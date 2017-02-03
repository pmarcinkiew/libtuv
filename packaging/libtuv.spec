Name:       libtuv
Summary:    libtuv
Version:    0.0.1
Release:    1
Group:      Application Framework/Package Management
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1001: %{name}.manifest

Requires:  unzip
Requires:  smack

BuildRequires:  cmake
#BuildRequires:  python
BuildRequires:  gettext-tools
#BuildRequires:  pkgconfig(dbus-glib-1)
##BuildRequires:  pkgconfig(glib-2.0)
#BuildRequires:  pkgconfig(gio-2.0)
BuildRequires:  pkgconfig(dlog)
#BuildRequires:  pkgconfig(bundle)
#BuildRequires:  pkgconfig(pkgmgr-info)
#BuildRequires:  pkgconfig(iniparser)
#BuildRequires:  pkgconfig(libtzplatform-config)
#BuildRequires:  pkgconfig(xdgmime)
#BuildRequires:  pkgconfig(db-util)
#BuildRequires:  pkgconfig(pkgmgr)
#BuildRequires:  pkgconfig(pkgmgr-installer)
#BuildRequires:  pkgconfig(aul)
#BuildRequires:  pkgmgr-info-parser-devel
#BuildRequires:  pkgmgr-info-parser
#BuildRequires:  fdupes
#Requires(posttrans):  /usr/bin/pkg_initdb

%description
libtuv

%prep
%setup -q
cp %{SOURCE1001} .

%build
TUV_PLATFORM=armv7l-tizen TUV_BOARD=artik make

%install
mkdir -p %{buildroot}/usr/bin
cp /usr/src/packages/BUILD/libtuv-0.0.1/build/armv7l-linux/debug/bin/tuvtester %{buildroot}/usr/bin
mkdir -p %{buildroot}%{_sysconfdir}/opt/upgrade

mkdir -p %{buildroot}/usr/share/license
cp LICENSE %{buildroot}/usr/share/license/%{name}

#%fdupes %{buildroot}

%post
#/sbin/ldconfig

# Update mime database to support package mime types
#update-mime-database %{_datadir}/mime
#chsmack -a '*' %{TZ_SYS_RW_PACKAGES}

%posttrans
#if [ ! -f %{TZ_SYS_DB}/.pkgmgr_parser.db ]; then
#  pkg_initdb --ro
#  install_preload_pkg
#  if [ -f /tmp/.preload_install_error ]; then
#    if [ ! -d /tmp/.postscript/error ]; then
#      mkdir -p /tmp/.postscript/error
#    fi
#    echo "preload install failed" > /tmp/.postscript/error/%{name}_error
#  else
#    pkgcmd -l
#  fi
#fi

%files
%manifest %{name}.manifest
%defattr(-,root,root,-)
%dir %{_sysconfdir}/opt/upgrade
%{_bindir}/tuvtester
#%{_bindir}/pkgcmd
#%{_bindir}/pkg_getsize
#%{_bindir}/pkg_cleardata
#%{_bindir}/pkginfo
#%{_bindir}/rsc-slice
#%{_bindir}/pkg_upgrade
#%attr(0755,root,root) %{_bindir}/install_preload_pkg
#%{_datadir}/mime/packages/mime.wac.xml
#%{_datadir}/mime/packages/mime.tpk.xml
#%attr(0700,root,root) /etc/package-manager/pkgmgr-unzip-pkg.sh
#%attr(0700,root,root) /etc/package-manager/pkgmgr-create-delta.sh
#%attr(0700,root,root) /usr/share/upgrade/scripts/700.pkgmgr.patch.sh
#%attr(0700,root,root) %{_sysconfdir}/opt/upgrade/pkgmgr.patch.sh
#%attr(0700,root,root) /usr/share/fixed_multiuser/scripts/pkgmgr-clear-skel.sh
/usr/share/license/%{name}
