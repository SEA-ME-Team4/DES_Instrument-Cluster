# Cross Compiling Qt For Rpi and Ubuntu

- Work on Ubuntu and make a cross-compiling environment so that compilation results are available on Raspberry Pi

---

## Prepare the Raspberry Pi

- for the Raspberry Pi, We used an **Ubuntu 20.04 Server**.

### 1. Kernel Update

To use cross compile, we have to update our Kernel

We updated to **5.15.84**

```cpp
sudo rpi-update cb852c1fa6660d69d14ea6d6debb067eefc3ffdf
```

the git hash is from https://github.com/raspberrypi/rpi-firmware

at `sudo raspi-config` , Make GL to Enable.

![Untitled (10)](https://github.com/SEA-ME/SEA-ME-Students/assets/106136905/125f4905-2af6-48f5-bf70-2fa890db5b9f)

### 2. Enable development source

`sudo vim /etc/apt/sources.list` 

Uncomment the following line by removing the # character (the line should exist already, if not then add it)

```cpp
deb-src http://raspbian.raspberrypi.org/raspbian/ buster main contrib non-free rpi
```

In our case, we used Ubuntu 20.04 Server on Rpi, so we uncommented every `deb-src` to enable development source.

### 3. Update system

```
sudo apt-get update
sudo apt-get dist-upgrade
sudo reboot
```

- check rsync

```
which rsync
# /usr/bin/rsync
```

- If rsync is not available [follow this link](https://snapcraft.io/install/rsync/raspbian)
- Add following structure  `sudo visudo`
    
    ```
    <username> ALL=NOPASSWD:/usr/bin/rsync
    ```
    

### 4. Install the required development packages

```
sudo apt-get build-dep qt5-qmake
sudo apt-get build-dep libqt5gui5
sudo apt-get build-dep libqt5webengine-data
sudo apt-get build-dep libqt5webkit5
sudo apt-get install libudev-dev libinput-dev libts-dev libxcb-xinerama0-dev libxcb-xinerama0 gdbserver
```

### 5. Create a directory for Qt install

```cpp
sudo mkdir /usr/local/qt5.15
sudo chown -R <username>:<username> /usr/local/qt5.15
```

---

## Ubuntu Machine(Host Computer)

- for the host system, We used an **Ubuntu 20.04 LTS**.

### 1. Update system

```
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install gcc git bison python gperf pkg-config gdb-multiarch
sudo apt install build-essential
```

### 2. **Set up the directory structure**

```
sudo mkdir ~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4
sudo mkdir ~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4/build
sudo mkdir ~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4/tools
sudo mkdir ~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4/sysroot
sudo mkdir ~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4/sysroot/usr
sudo mkdir ~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4/sysroot/opt
sudo chown -R 1000:1000 ~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4
cd ~/Documents/Qt-CrossCompile-RaspberryPi/raspberrypi4
```

### 3. Download Qt sources

- Down load Qt sources and unzip the file.

```
sudo wget http://download.qt.io/archive/qt/5.15/5.15.2/single/qt-everywhere-src-5.15.2.tar.xz
sudo tar xfv qt-everywhere-src-5.15.2.tar.xz
```


### 4. Add Device

- Add device `linux-rasp-pi-aarch64` to `~/Documents/QtCrossCompile-RaspberryPi/raspberrypi4/qt-everywhere-src-5.15.2/qtbase/mkspecs/devices/`because It wasn’t there.
- Copy `qmake.conf` and `qplatformdefs.h` from https://code.qt.io/cgit/qt/qtbase.git/tree/mkspecs/devices/linux-rasp-pi4-aarch64.

### 5. Download Cross-Compiler

- We used cross compiler package of **aarch64-linux-gnu**.

```
sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu
```

### 6 Sync our sysroot

- Remote synchronization Pull
    
    `rsync <options> <user-name>@<remote-host>:<source-file-dir> <destination>`
    
- Remote synchronization Push
    
    `rsync <options> <source-file-dir> <user-name>@<romote-host>:<destination>`
    

```
sudo rsync -avzS --delete --rsync-path="rsync" pi@IP:/lib/ sysroot/lib/
sudo rsync -avzS --delete --rsync-path="rsync" pi@IP:/usr/include/ sysroot/usr/include/
sudo rsync -avzS --delete --rsync-path="rsync" pi@IP:/usr/lib/ sysroot/usr/iib/
sudo rsync -avzS --delete --rsync-path="rsync" pi@IP:/opt/vc/ sysroot/opt/
```

- Fix symbolic link

```
sudo apt install symlinks
symlinks -rc sysroot
```

### 7. Configure Qt build

- build

```
cd build
../qt-everywhere-src-5.15.2/configure -release -opengl es2 -eglfs -device linux-rasp-pi4-aarch64 -device-option CROSS_COMPILE=aarch64-linux-gnu- -sysroot /opt/RaspberryQt/sysroot -prefix /usr/local/qt5.15 -extprefix /opt/RaspberryQt/qt5.15 -opensource -confirm-license -skip qtscript -skip qtwayland -skip qtwebengine -nomake tests -make libs -pkg-config -no-use-gold-linker -v -recheck
```

<details>
<summary>Troubleshooting</summary>
<div markdown="1">
    
- To prevent error, I add these 3 lines at the top of `~/Documents/Qt-CrossCompile-RaspberryPi/qt-everywhere-src-5.15.0/qtbase/src/corelib/global/qglobal.h`
    
    ```
    #ifdef __cplusplus
    #include <limits>
    #endif
    ```

</div>
</details>



### 8. Build Qt

- number following ‘-j’ is about your Core. match with your core.

```
make -j4 
make install
```

### 9. Deploy Qt to our Raspberry Pi

```
cd ~/rpi
sudo rsync -avzS --rsync-path="rsync" qt5.15/ $pi@$IP:/usr/local/qt5.15/
```
