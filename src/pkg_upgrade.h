/*
 * Copyright (c) 2000 - 2015 Samsung Electronics Co., Ltd. All rights reserved.
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

#ifndef PKG_FOTA_H_
#define PKG_FOTA_H_


#define TOKEN_TYPE_STR		"type="
#define TOKEN_PKGID_STR		"package="
#define TOKEN_VERSION_STR	"version="
#define TOKEN_PATH_STR		"path="
#define TOKEN_OPERATION_STR	"op="
#define TOKEN_REMOVE_STR	"removable="

#define SEPERATOR_END		'"'
#define SEPERATOR_MID		':'


#define ASCII(s) (const char *)s
#define XMLCHAR(s) (const xmlChar *)s

#define BUF_SIZE 1024
#define DIRECTORY_PERMISSION_755 0755
#define FOTA_RESULT_FILE	tzplatform_mkpath(TZ_SYS_GLOBALUSER_DATA, \
	"pkgmgr/fota/result.txt")

#ifndef FREE_AND_NULL
#define	FREE_AND_NULL(ptr) do {	\
		if (ptr) {	\
			free((void *)ptr);	\
			ptr = NULL;	\
		} \
} while(0)
#endif

#ifndef FREE_AND_STRDUP
#define	FREE_AND_STRDUP(from, to) do {	\
		if (to) free((void *)to);	\
		if (from) to = strdup(from);	\
} while(0)
#endif

#define _LOGE(fmt, arg...) do { \
	int fd = 0;\
	FILE* file = NULL;\
	file = fopen(FOTA_RESULT_FILE, "a");\
	if (file == NULL) break;\
	fprintf(file, "[PKG_FOTA][%5d][err]  "fmt"", getpid(), ##arg); \
	fflush(file);\
	fd = fileno(file);\
	fsync(fd);\
	fclose(file);\
	fprintf(stderr, "[PKG_FOTA][%5d][err]  "fmt"", getpid(), ##arg); \
} while (0)

#define	retvm_if(expr, val, fmt, arg...) do {	\
	if (expr) {	\
		_LOGE("(%s)"fmt, #expr, ##arg); \
		return (val);	\
	}	\
} while(0)

#define	err_if(expr, fmt, arg...) do {	\
	if (expr) { \
		_LOGE("(%s)"fmt, #expr, ##arg); \
	}	\
} while(0)

#define tryvm_if(expr, val, fmt, arg...) do { \
	if (expr) { \
		_LOGE("(%s)"fmt, #expr, ##arg); \
		val; \
		goto catch; \
	} \
} while (0)

typedef enum {
	PKG_IS_NOT_EXIST = 0,
	PKG_IS_SAME,
	PKG_IS_UPDATED,
	PKG_IS_INSERTED
} COMPARE_RESULT;

enum rpm_request_type {
	INSTALL_REQ,
	UNINSTALL_REQ,
	UPGRADE_REQ
};

#endif /* PKG_FOTA_H_ */
