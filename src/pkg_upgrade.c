/*
 * pkg-fota
 *
 * Copyright (c) 2000 - 2011 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#define _GNU_SOURCE

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <iniparser.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <libxml/xmlreader.h>

#include <package-manager-types.h>
#include <package-manager.h>
#include <pkgmgr_parser.h>
#include <pkgmgr-info.h>
#include "pkg_upgrade.h"

#include <tzplatform_config.h>

#define USR_MANIFEST_DIRECTORY	tzplatform_getenv(TZ_SYS_RO_PACKAGES)

#define PKGMGR_FOTA_PATH	tzplatform_mkpath(TZ_SYS_GLOBALUSER_DATA, \
	"pkgmgr/fota")
#define PKGID_LIST_FROM_DB_FILE	tzplatform_mkpath(TZ_SYS_GLOBALUSER_DATA, \
	"pkgmgr/fota/pkgid_list_from_db.txt")
#define PKGID_LIST_FROM_XML_FILE \
	tzplatform_mkpath(TZ_SYS_GLOBALUSER_DATA, \
	"pkgmgr/fota/pkgid_list_from_xml.txt")

#define PRELOAD_RW_TPK_PATH \
	tzplatform_mkpath(TZ_SYS_RO_APP, ".preload-rw-tpk")
#define PRELOAD_RW_WGT_PATH \
	tzplatform_mkpath(TZ_SYS_RO_APP, ".preload-rw-wgt")
#define PRELOAD_RW_FLAG_PATH \
	tzplatform_mkpath(TZ_SYS_RO_APP, ".preload-rw-flag")
#define PRELOAD_RW_LIST_FILE \
	tzplatform_mkpath(TZ_SYS_RO_APP, \
	".preload-rw-flag/restore_exception.list")

float __get_elapsed_time()
{
	static long start_time = 0;
	long endtime = 0;
	struct timeval tv;

	if (start_time == 0) {
		gettimeofday(&tv, NULL);
		start_time = tv.tv_sec * 1000l + tv.tv_usec / 1000l;
	}

	gettimeofday(&tv, NULL);
	endtime = tv.tv_sec * 1000l + tv.tv_usec / 1000l;

	return (endtime - start_time)/1000.0;
}

#define _LOG(fmt, arg...) do { \
	int fd = 0; \
	FILE *file = NULL; \
	file = fopen(FOTA_RESULT_FILE, "a"); \
	if (file == NULL) break; \
	fprintf(file, "[PKG_FOTA][%5d][%10.3fs]  "fmt"", getpid(), \
		__get_elapsed_time(), ##arg); \
	fflush(file); \
	fd = fileno(file); \
	fsync(fd); \
	fclose(file); \
	fprintf(stderr, "[PKG_FOTA][%5d][%10.3fs]  "fmt"", getpid(), \
		__get_elapsed_time(), ##arg); \
} while (0)

static int __is_dir(const char *dirname)
{
	struct stat stFileInfo;

	retvm_if(dirname == NULL, -1, "dirname == NULL\n");
	retvm_if(stat(dirname, &stFileInfo) < 0, -1,
		"stFileInfo is not enough\n");

	if (S_ISDIR(stFileInfo.st_mode))
		return 0;
	return -1;
}

static int __xsystem(const char *argv[])
{
	int status = 0;
	pid_t pid;
	pid = fork();
	switch (pid) {
	case -1:
		perror("fork failed");
		return -1;
	case 0:
		/* child */
		execvp(argv[0], (char *const *)argv);
		_exit(-1);
	default:
		/* parent */
		break;
	}
	if (waitpid(pid, &status, 0) == -1) {
		perror("waitpid failed");
		return -1;
	}
	if (WIFSIGNALED(status)) {
		perror("signal");
		return -1;
	}
	if (!WIFEXITED(status)) {
		/* shouldn't happen */
		perror("should not happen");
		return -1;
	}
	return WEXITSTATUS(status);
}

static int __check_pkgmgr_fota_dir()
{
	int ret = 0;

	if (__is_dir(PKGMGR_FOTA_PATH) < 0) {
		const char *mkdir_argv[] =  { "/bin/mkdir",
			"-p", PKGMGR_FOTA_PATH, NULL };
		ret = __xsystem(mkdir_argv);
		retvm_if(ret != 0, -1, "mkdir_argv error [%d]\n", ret);
	}

	return 0;
}

static int __remove_pkgid_list()
{
	int ret = 0;

	if (access(FOTA_RESULT_FILE, R_OK) == 0) {
		ret = remove(FOTA_RESULT_FILE);
		err_if(ret < 0, "remove[%s] failed", FOTA_RESULT_FILE);
	}

	if (access(PKGID_LIST_FROM_DB_FILE, R_OK) == 0) {
		ret = remove(PKGID_LIST_FROM_DB_FILE);
		err_if(ret < 0, "remove[%s] failed", PKGID_LIST_FROM_DB_FILE);
	}

	if (access(PKGID_LIST_FROM_XML_FILE, R_OK) == 0) {
		ret = remove(PKGID_LIST_FROM_XML_FILE);
		err_if(ret < 0, "remove[%s] failed", PKGID_LIST_FROM_XML_FILE);
	}

	return 0;
}

static int __make_pkgid_list(const char *file_path, char *pkgid,
		char *version, char *type)
{
	FILE *fp;\

	if (NULL == pkgid)
		return 0;

	fp = fopen(file_path, "a+");
	if (NULL == fp)
		return -1;

	fprintf(fp, "%s\"%s\"   %s\"%s\"   %s\"%s\":\n", TOKEN_PKGID_STR,
		pkgid, TOKEN_VERSION_STR, version, TOKEN_TYPE_STR, type);

	fclose(fp);\

	return 0;
}

static int __pkgid_list_cb(const pkgmgrinfo_pkginfo_h handle, void *user_data)
{
	int ret = -1;
	char *pkgid = NULL;
	char *version = NULL;
	char *type = NULL;

	ret = pkgmgrinfo_pkginfo_get_pkgid(handle, &pkgid);
	err_if(ret < 0, "pkgmgrinfo_pkginfo_get_pkgid failed");

	ret = pkgmgrinfo_pkginfo_get_version(handle, &version);
	err_if(ret < 0, "pkgmgrinfo_pkginfo_get_version failed");

	ret = pkgmgrinfo_pkginfo_get_type(handle, &type);
	err_if(ret < 0, "pkgmgrinfo_pkginfo_get_type failed");

	ret = __make_pkgid_list((char *)user_data, pkgid, version, type);
	return ret;
}

static void __str_trim(char *input)
{
	char *trim_str = input;

	if (input == NULL)
		return;

	while (*input != 0) {
		if (!isspace(*input)) {
			*trim_str = *input;
			trim_str++;
		}
		input++;
	}

	*trim_str = 0;
	return;
}

static char *__getvalue(const char *pBuf, const char *pKey, int depth)
{
	const char *p = NULL;
	const char *pStart = NULL;
	const char *pEnd = NULL;

	p = strstr(pBuf, pKey);
	if (p == NULL)
		return NULL;

	pStart = p + strlen(pKey) + depth;
	pEnd = strchr(pStart, SEPERATOR_END);
	if (pEnd == NULL) {
		pEnd = strchr(pStart, SEPERATOR_MID);
		if (pEnd == NULL)
			return NULL;
	}

	size_t len = pEnd - pStart;
	if (len <= 0)
		return NULL;

	char *pRes = (char *)malloc(len + 1);
	if (pRes == NULL) {
		_LOG("malloc failed.\n");
		return NULL;
	}
	strncpy(pRes, pStart, len);
	pRes[len] = 0;

	return pRes;
}

static int __compare_pkgid(char *file_path, char *fota_pkgid,
		char *fota_version)
{
	retvm_if(file_path == NULL, -1, "file_path is null.\n");
	retvm_if(fota_pkgid == NULL, -1, "fota_pkgid is null.\n");
	retvm_if(fota_version == NULL, -1, "fota_version is null.\n");

	int ret = PKG_IS_NOT_EXIST;
	FILE *fp = NULL;
	char buf[BUF_SIZE] = {0};
	char *pkgid = NULL;
	char *version = NULL;
	int compare = PMINFO_VERSION_SAME;

	fp = fopen(file_path, "r");
	retvm_if(fp == NULL, -1, "Fail get : %s\n", file_path);

	while (fgets(buf, BUF_SIZE, fp) != NULL) {
		__str_trim(buf);

		pkgid = __getvalue(buf, TOKEN_PKGID_STR, 1);
		if (pkgid == NULL) {
			_LOG("pkgid is null\n");
			continue;
		}

		version = __getvalue(buf, TOKEN_VERSION_STR, 1);

		if (version == NULL) {
			FREE_AND_NULL(pkgid);
			_LOG("compare_data is null\n");
			continue;
		}

		if (strcmp(pkgid, fota_pkgid) == 0) {
			ret = pkgmgrinfo_compare_package_version(version,
				fota_version, &compare);
			if (compare == PMINFO_VERSION_NEW) {
				_LOG("pkgid = %s, db version = %s, new package"
					" version = %s\n", pkgid, version,
						fota_version);
				_LOG("pkg is updated, need to upgrade\n");

				ret = PKG_IS_UPDATED;
				FREE_AND_NULL(pkgid);
				FREE_AND_NULL(version);
				break;
			}

			FREE_AND_NULL(pkgid);
			FREE_AND_NULL(version);
			ret =  PKG_IS_SAME;
			break;
		}

		FREE_AND_NULL(pkgid);
		FREE_AND_NULL(version);
		memset(buf, 0x00, BUF_SIZE);
	}

	if (fp != NULL)
		fclose(fp);

	return ret;
}

static int __compare_builtin_removable_pkgid(const char *pkgid)
{
	retvm_if(pkgid == NULL, 0, "pkgid is null\n");

	int ret = 0;
	FILE *fp = NULL;
	char buf[BUF_SIZE] = {0};

	fp = fopen(PRELOAD_RW_LIST_FILE, "r");
	if (fp == NULL)
		return ret;

	while (fgets(buf, BUF_SIZE, fp) != NULL) {
		__str_trim(buf);

		if (strcmp(buf + strlen("/opt/usr/apps/"), pkgid) == 0) {
			_LOG("pkgid[%s] will be processed by builtin cmd.\n",
				pkgid);
			ret = -1;
			break;
		}

		memset(buf, 0x00, BUF_SIZE);
	}

	if (fp != NULL)
		fclose(fp);

	return ret;
}

char *__manifest_to_package(const char *manifest)
{
	char *package;

	if (manifest == NULL)
		return NULL;

	package = strdup(manifest);
	if (package == NULL)
		return NULL;

	if (!strstr(package, ".xml")) {
		_LOG("%s is not a manifest file \n", manifest);
		free(package);
		return NULL;
	}

	return package;
}

static int __verify_uninstall_operation(char *pkgid)
{
	int ret = 0;
	bool update = false;
	bool system = false;
	pkgmgrinfo_pkginfo_h handle = NULL;

	ret = pkgmgrinfo_pkginfo_get_pkginfo(pkgid, &handle);
	retvm_if(ret < 0, 0, "Failed to get handle\n");

	ret = pkgmgrinfo_pkginfo_is_update(handle, &update);
	tryvm_if(ret < 0, ret = 0, "Failed to get update\n");

	ret = pkgmgrinfo_pkginfo_is_system(handle, &system);
	tryvm_if(ret < 0, ret = 0, "Failed to get system\n");

	if (system && update)
		ret = -1;
	else
		ret = 0;

catch:
	pkgmgrinfo_pkginfo_destroy_pkginfo(handle);
	return ret;
}

static void __send_args_to_backend(char *pkgid, int compare_result)
{
	int ret = 0;

	long starttime;
	long endtime;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	starttime = tv.tv_sec * 1000l + tv.tv_usec / 1000l;

	const char *install_ro[] = { "/usr/bin/tpk-backend", "-y", pkgid,
				"--preload", "--partial-rw", NULL };
	const char *uninstall_ro[] = { "/usr/bin/tpk-backend", "-d", pkgid,
				"--preload", "--force-remove", "--partial-rw", NULL };

	if (compare_result == PKG_IS_SAME)
		return;

	if (__compare_builtin_removable_pkgid(pkgid) < 0)
		return;

	switch (compare_result) {
	case PKG_IS_INSERTED:
	case PKG_IS_UPDATED:
		ret = __xsystem(install_ro);
		break;

	case PKG_IS_NOT_EXIST:
		ret = __verify_uninstall_operation(pkgid);
		if (ret < 0) {
			_LOG("pkgid[%s] is updated system, "
				"Do not uninstall it\n", pkgid);
			return;
		}

		ret = __xsystem(uninstall_ro);
		break;
	default:
		break;
	}

	gettimeofday(&tv, NULL);
	endtime = tv.tv_sec * 1000l + tv.tv_usec / 1000l;

	_LOG("result[%ld ms, %d] \t Pkgid[%s]  \n",
		(endtime - starttime), ret, pkgid);
}

int __child_element(xmlTextReaderPtr reader, int depth)
{
	int ret = xmlTextReaderRead(reader);
	int cur = xmlTextReaderDepth(reader);
	while (ret == 1) {
		switch (xmlTextReaderNodeType(reader)) {
		case XML_READER_TYPE_ELEMENT:
			if (cur == depth + 1)
				return 1;
			break;
		case XML_READER_TYPE_TEXT:
			/*text is handled by each function separately*/
			if (cur == depth + 1)
				return 0;
			break;
		case XML_READER_TYPE_END_ELEMENT:
			if (cur == depth)
				return 0;
			break;
		default:
			if (cur <= depth)
				return 0;
			break;
		}

		ret = xmlTextReaderRead(reader);
		cur = xmlTextReaderDepth(reader);
	}
	return ret;
}

char *__find_info_from_xml(const char *manifest, const char *find_info)
{
	retvm_if(manifest == NULL, NULL, "manifest is null.\n");
	retvm_if(find_info == NULL, NULL, "find_info is null.\n");

	const xmlChar *node;
	xmlTextReaderPtr reader;
	char *info_val = NULL;
	xmlChar *tmp = NULL;

	reader = xmlReaderForFile(manifest, NULL, 0);

	if (reader) {
		if (__child_element(reader, -1)) {
			node = xmlTextReaderConstName(reader);
			if (!node) {
				printf("xmlTextReaderConstName value is NULL\n");
				goto end;
			}

			if (!strcmp(ASCII(node), "manifest")) {
				tmp = xmlTextReaderGetAttribute(reader,
					XMLCHAR(find_info));
				if (tmp) {
					FREE_AND_STRDUP(ASCII(tmp), info_val);
					if (info_val == NULL)
						printf("Malloc Failed\n");
					FREE_AND_NULL(tmp);
				}
			} else {
				printf("Manifest Node is not found\n");
			}
		}
	} else {
		printf("xmlReaderForFile value is NULL\n");
	}

end:
	if (reader)
		xmlFreeTextReader(reader);

	return info_val;
}

static int __find_preload_pkgid_from_xml(const char *file_path,
		const char *xml_directory)
{
	retvm_if(file_path == NULL, -1, "file_path is NULL.\n");
	retvm_if(xml_directory == NULL, -1, "xml_directory is NULL.\n");

	int ret = 0;
	char buf[BUF_SIZE] = {0};
	DIR *dir;
	struct dirent entry, *result;

	dir = opendir(xml_directory);
	if (!dir) {
		if (strerror_r(errno, buf, sizeof(buf)) == 0)
			_LOG("Failed to access the [%s] because %s\n",
				xml_directory, buf);
		return -1;
	}

	for (ret = readdir_r(dir, &entry, &result);
			ret == 0 && result != NULL;
			ret = readdir_r(dir, &entry, &result)) {
		char *manifest = NULL;
		char *pkgid = NULL;
		char *version = NULL;
		char *type = NULL;

		if (entry.d_name[0] == '.') continue;

		manifest = __manifest_to_package(entry.d_name);
		if (!manifest) {
			_LOG("Failed to convert file to xml[%s]\n",
				entry.d_name);
			continue;
		}

		snprintf(buf, sizeof(buf), "%s/%s", xml_directory, manifest);

		/*Get the package name from manifest file*/
		pkgid = __find_info_from_xml(buf, "package");
		if (pkgid == NULL) {
			FREE_AND_NULL(manifest);
			continue;
		}

		version = __find_info_from_xml(buf, "version");
		if (version == NULL)
			version = strdup("0.0.1");

		type = __find_info_from_xml(buf, "type");
		if (type == NULL)
			type = strdup("tpk");

		ret = __make_pkgid_list((char *)file_path, pkgid,
			version, type);
		if (ret < 0)
			_LOG("Make file Fail : %s => %s, %s\n",
				buf, pkgid, version);

		FREE_AND_NULL(pkgid);
		FREE_AND_NULL(version);
		FREE_AND_NULL(manifest);
		FREE_AND_NULL(type);
	}

	closedir(dir);

	return 0;
}

static int __find_preload_pkgid_from_db(const char *file_path)
{
	retvm_if(file_path == NULL, -1, "file_path is NULL.\n");

	int ret = 0;
	pkgmgrinfo_pkginfo_filter_h handle = NULL;

	ret = pkgmgrinfo_pkginfo_filter_create(&handle);
	retvm_if(ret != PMINFO_R_OK, -1,
		"pkginfo filter handle create failed\n");

	ret = pkgmgrinfo_pkginfo_filter_add_bool(handle,
		PMINFO_PKGINFO_PROP_PACKAGE_PRELOAD, 1);
	tryvm_if(ret < 0, ret = -1, "pkgmgrinfo_pkginfo_filter_add_bool"
		"(PMINFO_PKGINFO_PROP_PACKAGE_PRELOAD) failed\n");

	ret = pkgmgrinfo_pkginfo_filter_add_bool(handle,
		PMINFO_PKGINFO_PROP_PACKAGE_READONLY, 1);
	tryvm_if(ret < 0, ret = -1, "pkgmgrinfo_pkginfo_filter_add_bool"
		"(PMINFO_PKGINFO_PROP_PACKAGE_READONLY) failed\n");

	ret = pkgmgrinfo_pkginfo_filter_foreach_pkginfo(handle,
		__pkgid_list_cb, (void *)file_path);
	err_if(ret < 0,
		"pkgmgrinfo_pkginfo_filter_foreach_pkginfo() failed\n");

catch:
	pkgmgrinfo_pkginfo_filter_destroy(handle);
	return ret;
}

static int __find_matched_pkgid_from_list(const char *source_file,
		const char *target_file)
{
	retvm_if(source_file == NULL, -1, "source_file is NULL.\n");
	retvm_if(target_file == NULL, -1, "target_file is NULL.\n");

	FILE *fp = NULL;
	char buf[BUF_SIZE] = {0};
	char *pkgid = NULL;
	char *version = NULL;

	int same_pkg_cnt = 0;
	int update_pkg_cnt = 0;
	int insert_pkg_cnt = 0;
	int total_pkg_cnt = 0;

	int compare_result = 0;

	fp = fopen(source_file, "r");
	retvm_if(fp == NULL, -1, "Fail get : %s\n", source_file);

	_LOG("Searching...... inserted  or  Updated package \n");

	while (fgets(buf, BUF_SIZE, fp) != NULL) {
		__str_trim(buf);

		pkgid = __getvalue(buf, TOKEN_PKGID_STR, 1);
		if (pkgid == NULL)
			continue;

		version = __getvalue(buf, TOKEN_VERSION_STR, 1);

		compare_result = __compare_pkgid((char *)target_file, pkgid,
						version);
		if (compare_result == PKG_IS_NOT_EXIST) {
			_LOG("pkgid[%s] is installed, Start install\n", pkgid);
			compare_result = PKG_IS_INSERTED;
			insert_pkg_cnt++;
		} else if (compare_result == PKG_IS_SAME) {
			same_pkg_cnt++;
		} else if (compare_result == PKG_IS_UPDATED) {
			update_pkg_cnt++;
		}

		total_pkg_cnt++;
		__send_args_to_backend(pkgid, compare_result);

		memset(buf, 0x00, BUF_SIZE);
		FREE_AND_NULL(pkgid);
		FREE_AND_NULL(version);
	}

	_LOG("-------------------------------------------------------\n");
	_LOG("[Total pkg=%d, same pkg=%d, updated pkg=%d, "
		"inserted package=%d]\n",
		total_pkg_cnt, same_pkg_cnt, update_pkg_cnt, insert_pkg_cnt);
	_LOG("-------------------------------------------------------\n");

	if (fp != NULL)
		fclose(fp);

	return 0;
}

static int __find_deleted_pkgid_from_list(const char *source_file,
		const char *target_file)
{
	retvm_if(source_file == NULL, -1, "source_file is NULL.\n");
	retvm_if(target_file == NULL, -1, "target_file is NULL.\n");

	FILE *fp = NULL;
	char buf[BUF_SIZE] = {0};
	char *pkgid = NULL;
	char *version = NULL;

	int deleted_pkg_cnt = 0;
	int total_pkg_cnt = 0;

	int compare_result = 0;

	fp = fopen(source_file, "r");
	retvm_if(fp == NULL, -1, "Fail get : %s\n", source_file);

	_LOG("Searching...... deleted package \n");

	while (fgets(buf, BUF_SIZE, fp) != NULL) {
		__str_trim(buf);

		pkgid = __getvalue(buf, TOKEN_PKGID_STR, 1);
		if (pkgid == NULL)
			continue;

		version = __getvalue(buf, TOKEN_VERSION_STR, 1);

		compare_result = __compare_pkgid((char *)target_file, pkgid,
						version);
		if (compare_result == PKG_IS_NOT_EXIST) {
			_LOG("pkgid[%s] is uninstall, Start uninstall\n",
				pkgid);
			__send_args_to_backend(pkgid, compare_result);

			deleted_pkg_cnt++;
		}
		total_pkg_cnt++;

		memset(buf, 0x00, BUF_SIZE);
		FREE_AND_NULL(pkgid);
		FREE_AND_NULL(version);
	}

	_LOG("-------------------------------------------------------\n");
	_LOG("[Total pkg=%d, deleted package=%d]\n",
		total_pkg_cnt, deleted_pkg_cnt);
	_LOG("-------------------------------------------------------\n");

	if (fp != NULL)
		fclose(fp);

	return 0;

}

static int __get_pkgid_list_from_db_and_xml()
{
	_LOG("=======================================================\n");
	_LOG("RO preload package fota\n");
	_LOG("=======================================================\n");

	int ret = 0;

	/*get pkg info on pkgmgr db, it means old version */
	ret = __find_preload_pkgid_from_db(PKGID_LIST_FROM_DB_FILE);
	retvm_if(ret < 0, -1, "__find_preload_pkgid_from_db fail.\n");

	_LOG("Make pkgid list from db success!! \n");

	/*get pkg info on xml, it means new version */
	ret = __find_preload_pkgid_from_xml(PKGID_LIST_FROM_XML_FILE,
		USR_MANIFEST_DIRECTORY);
	retvm_if(ret < 0, -1, "__find_preload_pkgid_from_xml fail.\n");

	_LOG("Make pkgid list from xml success!! \n");

	return 0;
}

static int __process_ro_fota()
{
	int ret;
	long starttime;
	long endtime;
	struct timeval tv;

	xmlInitParser();

	gettimeofday(&tv, NULL);
	starttime = tv.tv_sec * 1000l + tv.tv_usec / 1000l;

	/*check pkgmgr-fota dir, if it is not, then exit*/
	ret = __check_pkgmgr_fota_dir();
	retvm_if(ret < 0, -1, "__check_pkgmgr_fota_dir is failed.\n");

	/*clean pkgid list file*/
	ret = __remove_pkgid_list();
	err_if(ret < 0, "remove[%s] failed\n", FOTA_RESULT_FILE);

	/*get pkgid from orginal pkgmgr db*/
	ret = __get_pkgid_list_from_db_and_xml();
	retvm_if(ret < 0, -1, "__get_pkgid_list_from_db_and_xml is failed.\n");

	/*find deleted pkgid*/
	ret = __find_deleted_pkgid_from_list(PKGID_LIST_FROM_DB_FILE,
		PKGID_LIST_FROM_XML_FILE);
	err_if(ret < 0, "__find_deleted_pkgid_from_list fail.\n");

	/*find updated, inserted pkgid*/
	ret = __find_matched_pkgid_from_list(PKGID_LIST_FROM_XML_FILE,
		PKGID_LIST_FROM_DB_FILE);
	err_if(ret < 0, "__find_matched_pkgid_from_list fail.\n");

	gettimeofday(&tv, NULL);
	endtime = tv.tv_sec * 1000l + tv.tv_usec / 1000l;

	_LOG("=======================================================\n");
	_LOG("End RO process[time : %ld ms]\n", endtime - starttime);
	_LOG("=======================================================\n");

	xmlCleanupParser();

	return 0;
}

static int __process_rw_fota(const char *directory)
{
	retvm_if(directory == NULL, -1, "directory is null\n");

	int ret = -1;
	char file_path[BUF_SIZE] = {'\0'};
	DIR *dir;
	struct dirent entry, *result;
	long total_time = 0;

	dir = opendir(directory);
	retvm_if(dir == NULL, -1, "Failed to access the [%s]\n", directory);

	_LOG("=======================================================\n");
	_LOG("RW preload package fota\n");
	_LOG("=======================================================\n");

	for (ret = readdir_r(dir, &entry, &result);
			ret == 0 && result != NULL;
			ret = readdir_r(dir, &entry, &result)) {

		if (entry.d_name[0] == '.') continue;

		snprintf(file_path, sizeof(file_path), "%s/%s", directory,
			entry.d_name);

		_LOG("---------------------------------------------------\n");
		_LOG(" start request : %s\n", file_path);

		int compare = PMINFO_VERSION_SAME;
		long starttime;
		long endtime;
		struct timeval tv;

		gettimeofday(&tv, NULL);
		starttime = tv.tv_sec * 1000l + tv.tv_usec / 1000l;

		char *version = NULL;
		pkgmgrinfo_pkginfo_h handle = NULL;
		package_manager_pkg_detail_info_t *pkg_info = NULL;

		pkg_info = pkgmgr_client_check_pkginfo_from_file(file_path);
		if (pkg_info == NULL) {
			_LOG("can not get pkg_info from [%s]\n", file_path);
			continue;
		}

		ret = pkgmgrinfo_pkginfo_get_pkginfo(pkg_info->pkgid, &handle);
		if (ret == PMINFO_R_OK) {
			ret = pkgmgrinfo_pkginfo_get_version(handle, &version);
			if (ret != PMINFO_R_OK) {
				_LOG("can not get pkg version[%s]\n",
					pkg_info->pkgid);
				pkgmgrinfo_pkginfo_destroy_pkginfo(handle);
				continue;
			}

			_LOG("pkgid = %s, db version = %s, "
				"new package version = %s\n",
				pkg_info->pkgid, version, pkg_info->version);

			ret = pkgmgrinfo_compare_package_version(version,
					pkg_info->version, &compare);
			if (compare != PMINFO_VERSION_NEW) {
				/* package version is not update on FOTA. */
				_LOG("pkg is not updated\n");
				pkgmgrinfo_pkginfo_destroy_pkginfo(handle);

				gettimeofday(&tv, NULL);
				endtime = tv.tv_sec * 1000l +
					tv.tv_usec / 1000l;
				total_time += (int)(endtime - starttime);
				_LOG("finish request [time : %d ms]\n",
					(int)(endtime - starttime));
				continue;
			}

			_LOG("pkg is updated, need to upgrade\n");
			pkgmgrinfo_pkginfo_destroy_pkginfo(handle);
		} else {
			char flag_path[BUF_SIZE] = { 0, };
			snprintf(flag_path, BUF_SIZE, "%s/%s",
				PRELOAD_RW_FLAG_PATH, pkg_info->pkgid);
			if (access(flag_path, F_OK) == 0) {
				_LOG("pkgid[%s] is installed before and "
					"uninstalled by user !! \n",
					pkg_info->pkgid);
				gettimeofday(&tv, NULL);
				endtime = tv.tv_sec * 1000l +
					tv.tv_usec / 1000l;
				total_time += (int)(endtime - starttime);
				_LOG("finish request [time : %d ms]\n",
					(int)(endtime - starttime));
				continue;
			}

			_LOG("pkgid[%s] is new\n", pkg_info->pkgid);
		}

		const char *install_rw[] = { "/usr/bin/tpk-backend", "-y",
			pkg_info->pkgid, "--preload-rw", NULL };
		ret = __xsystem(install_rw);
		if (ret == 0)
			_LOG("success request\n");
		else
			_LOG("fail request : %d\n", ret);

		pkgmgr_client_free_pkginfo(pkg_info);

		gettimeofday(&tv, NULL);
		endtime = tv.tv_sec * 1000l + tv.tv_usec / 1000l;
		total_time += (int)(endtime - starttime);
		_LOG("finish request [time : %d ms]\n",
			(int)(endtime - starttime));
	}

	closedir(dir);
	_LOG("=======================================================\n");
	_LOG("End RW process[time : %d ms]\n", (int)total_time);
	_LOG("=======================================================\n");
	return 0;
}

int main(int argc, char *argv[])
{
	int ret = 0;

	if (argc == 2) {
		if (strcmp(argv[1], "-rof") == 0) {
			ret = __process_ro_fota();
			retvm_if(ret < 0, EXIT_FAILURE,
				"__process_ro_fota is failed.\n");
		} else if (strcmp(argv[1], "-rwf") == 0) {
			ret = __process_rw_fota(PRELOAD_RW_TPK_PATH);
			retvm_if(ret < 0, EXIT_FAILURE,
				"PRELOAD_RW_TPK_PATH is failed.\n");
			ret = __process_rw_fota(PRELOAD_RW_WGT_PATH);
			retvm_if(ret < 0, EXIT_FAILURE,
				"PRELOAD_RW_WGT_PATH is failed.\n");
		} else {
			fprintf(stderr, "not supported operand\n");
		}
	} else {
		fprintf(stderr, "mising operand\n");
	}

	return EXIT_SUCCESS;
}
