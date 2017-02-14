You can find project details in [wiki](https://github.com/Samsung/libtuv/wiki)

Tizen Artik build:

### How to Build

This is temporary version of Tizen Artik 10 repo. It can't be build with standard make script. It is modified to work correctly only with GBS environment
Compilation in GBS:

```
# gbs build -A armv7l --debug
```

It works only at root.


GBS conf

```
# cat ~/.gbs.conf
[general]
tmpdir=/var/tmp/
profile = profile.common.tizen3.0.artik
work_dir=.

[repo.tizen3.0.artik]
url = http://download.tizen.org/snapshots/tizen/common_artik/tizen-common-artik_20170116.1/repos/arm-wayland/packages/
#https://download.tizen.org/snapshots/tizen/common/latest/repos/arm-wayland/packages/

[repo.tizen.base]
url = http://download.tizen.org/snapshots/tizen/base/latest/repos/arm/packages/

[profile.common.tizen3.0.artik]
repos=repo.tizen3.0.artik, repo.tizen.base
```

### Installation

```
PC$sdb connect IP

PC$sdb root on
PC$sdb push file folder
PC$sdb shell

tizen# rpm -i package.rpm
```

### How to Test

TODO


