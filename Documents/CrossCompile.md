# Cross Compilie Qt For Rpi and Ubuntu

- Make Cross Compile environment so that compiled results are available on Raspberry Pi.

---

## Prepare the Raspberry Pi

- For the Raspberry Pi, We used **Raspberry Pi OS Lite (64-bit).**

### 1. Enable development source

- Uncomment the following line in `sudo vim /etc/apt/sources.list` by removing the # character. (the line should exist already, if not then add it.)

```
deb-src <http://raspbian.raspberrypi.org/raspbian/> buster main contrib non-free rpi
```

### 2. Update system and set rsync

```bash
sudo apt-get update
sudo apt-get upgrade
sudo reboot
```

- check path of rsync.

```bash
which rsync
# /usr/bin/rsync
```

- If rsync is not available [follow this link](https://snapcraft.io/install/rsync/raspbian).
- Add following structure in `sudo visudo`.

```
<username> ALL=NOPASSWD:/usr/bin/rsync
```

### 4. Install the required development packages

```bash
sudo apt-get build-dep qt5-qmake
sudo apt-get build-dep libqt5gui5
sudo apt-get build-dep libqt5webengine-data
sudo apt-get build-dep libqt5webkit5
sudo apt-get install libudev-dev libinput-dev libts-dev libxcb-xinerama0-dev libxcb-xinerama0 gdbserver

# Graphic Package
sudo apt-get install mesa-utils
```

### 5. Create a directory for rsync Qt from Host Computer

```bash
sudo mkdir /usr/local/qt5.15
sudo chown -R <username>:<username> /usr/local/qt5.15
```

---

## Ubuntu Machine(Host Computer)

- for the host system, We used **Ubuntu 20.04 LTS**.

### 1. Update system

```bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install gcc git bison python gperf pkg-config gdb-multiarch
sudo apt install build-essential
```

### 2. **Set up the directory structure**

```bash
sudo mkdir ~/rpi
sudo mkdir ~/rpi/build
sudo mkdir ~/rpi/tools
sudo mkdir ~/rpi/sysroot
sudo mkdir ~/rpi/sysroot/usr
sudo mkdir ~/rpi/sysroot/opt
sudo chown -R 1000:1000 ~/rpi
cd ~/rpi
```

### 3. Download Qt sources

- Download Qt sources and Unzip the file. (Qt Version 5.15.2)

```bash
sudo wget <http://download.qt.io/archive/qt/5.15/5.15.2/single/qt-everywhere-src-5.15.2.tar.xz>
sudo tar xfv qt-everywhere-src-5.15.2.tar.xz
```

### 4. Add Device

- Our target Device is `linux-rasp-pi-aarch64`.
- Add device `linux-rasp-pi-aarch64` to `~/rpi/raspberrypi4/qt-everywhere-src-5.15.2/qtbase/mkspecs/devices/` if you don’t have.
- Copy `qmake.conf` and `qplatformdefs.h` from [Qt repository](https://code.qt.io/cgit/qt/qtbase.git/tree/mkspecs/devices/linux-rasp-pi4-aarch64)

### 5. Download Cross-Compiler

- We used cross compiler package of **aarch64-linux-gnu**.

```bash
sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu
```

### 6 Sync our sysroot

- Remote synchronization Pull
    
    `rsync <options> <user-name>@<remote-host>:<source-file-dir> <destination>`
    
- Remote synchronization Push
    
    `rsync <options> <source-file-dir> <user-name>@<romote-host>:<destination>`
    

```bash
sudo rsync -avzS --delete --rsync-path="rsync" {username}@{IP_address}:/lib/ sysroot/lib/
sudo rsync -avzS --delete --rsync-path="rsync" {username}@{IP_address}:/usr/include/ sysroot/usr/include/
sudo rsync -avzS --delete --rsync-path="rsync" {username}@{IP_address}:/usr/lib/ sysroot/usr/iib/
```

- Fix symbolic link

```bash
sudo apt install symlinks
symlinks -rc sysroot/
```

### 7. Configure Qt build

- build

```bash
cd build
../qt-everywhere-src-5.15.2/configure -release -opengl es2 -eglfs -device linux-rasp-pi4-aarch64 -device-option CROSS_COMPILE=aarch64-linux-gnu- -sysroot ~/rpi/sysroot -prefix /usr/local/qt5.15 -extprefix ~/rpi/qt5.15 -opensource -confirm-license -skip qtscript -skip qtwayland -skip qtwebengine -nomake tests -make libs -pkg-config -no-use-gold-linker -v -recheck
```

- If you need to rebuild, make sure that no files in build folder.

### 8. Build Qt

- number following ‘-j’ is about your Core.
- `$(nproc)` will automatically match with your core.

```bash
make -j $(nproc)
make install
```

### 9. Deploy Qt to our Raspberry Pi

```bash
cd ~/rpi
sudo rsync -avzS --rsync-path="rsync" qt5.15/ {username}@{IP_address}:/usr/local/qt5.15/
```

---

## **Reference**

1. [Qt 5.15.2 Download](https://download.qt.io/official_releases/qt/5.15/5.15.2/)
2. [linux-rasp-pi4-aarch64 source](https://code.qt.io/cgit/qt/qtbase.git/tree/mkspecs/devices/linux-rasp-pi4-aarch64)
3. [Cross-Compile Qt 6 for Raspberry Pi (also helpful for Qt 5.15)](https://wiki.qt.io/Cross-Compile_Qt_6_for_Raspberry_Pi)
4. [Cross compiling for arm or aarch64 on Debian or Ubuntu (Concept of CrossCompile)](https://jensd.be/1126/linux/cross-compiling-for-arm-or-aarch64-on-debian-or-ubuntu)
