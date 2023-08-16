# Qt Creator configuration

### **Qt Creator Version : 4.11.0**

### 1. Add Qt version (Tool -> Options -> Kits -> Qt Versions)

![Untitled](https://github.com/SEA-ME-Team4/DES_Instrument-Cluster/assets/120576021/79bb5943-c2e8-4a6e-ab52-010165d51854)

(1) Click Add

(2) Find ‘qmake’ whick is made by CrossCompile (rpi/qt5.15/bin/qmake)

### 2. Device Setting (Tool -> Options -> Devices)

![Untitled (1)](https://github.com/SEA-ME-Team4/DES_Instrument-Cluster/assets/120576021/355e261d-f828-4b37-9ab4-92b9ac83a317)

(1) Click Add -> Generic Linux Device

(2) Enter Name, IP address, username of Raspberry Pi

(3) Generate and Deploy Key for authentication (Optional)

(4) Click Finish, then application automatically test device connectivity

### 3. Kits Setting (Tool -> Options -> Kits -> Add)

![Untitled (2)](https://github.com/SEA-ME-Team4/DES_Instrument-Cluster/assets/120576021/3b511280-0dd4-4477-97d8-33a918e62e65)

(1) Set Name of Kits

(2) Select the device you just created

(3) Select the sysroot loaded by rsync (Optional, we didn’t)

(4) Choose arm 64bit complier for aarch64 architecture 

(5) Choose Qt version made by CrossCompile

### 4. Set Release Path (in `projectname.pro`)

Add (or Modify) following line to ‘.pro’ for release excecution file automatically

```makefile
target.file = {your_project_name}
target.path = /home/{your_username}/{optional}
INSTALLS += target
```

Of course, SSH connection is needed

### 5. Use Linux Frame Buffer as platform of Qt execution files

Use following `-platform` command-line argument for set plugin.

```bash
./{application_name} -platform linuxfb
```

Also, you can use `QT_QPA_PLATFORM` to set environment variable.

```bash
QT_QPA_PLATFORM=linuxfb:fb=/dev/fb0
```

### 6. (Optional) Set environment variable permanently

For setting environment variable permanently, you need to modify `~/.bashrc`.
(This is just for login shell. If you want to modify nonlogin shell, modify `/etc/bash.bashrc`)

```bash
sudo nano ~/.bashrc
```

Add following line in the last of file.

```bash
QT_QPA_PLATFORM=linuxfb:fb=/dev/fb0
```

Open new terminal or source your updated `bashrc` file.

```bash
source ~/.bashrc
```

From now on, you don’t need -`platform` argument for using Linux Frame Buffer.

### 7. (Optional) Turn off Terminal Blink

For Raspberry Pi OS Lite Version, `fb0` is for terminal.
So, blink of cursor can make your application annoying.

You can turn off blink of cursor by using following command

```bash
# Only on Raspberry Pi terminal (not by SSH)
sudo setterm -cursor off
```

 Also you can add this in `~/.bashrc`.

```bash
sudo nano ~/.bashrc
```

And you need to source your `.bashrc` file

```bash
source ~/.bashrc
```

### 8. (Optional) Notice

In reference, we can see that rotation can be done with `QT_QPA_EGLFS_ROTATION`.

```bash
export QT_QPA_EGLFS_ROTATION=90
```

But, for us, it doesn’t work.
So we decide to make our application(qml) show rotated display.

---

## Reference

1. [Remote Qt development](https://kampi.gitbook.io/raspberry-pi/remote-qt-development)
2. [Qt for Embedded Linux (LinuxFB)](https://doc.qt.io/qt-5/embedded-linux.html)
