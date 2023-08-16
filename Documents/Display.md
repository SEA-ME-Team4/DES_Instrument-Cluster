## 1. Hardware Connection

Connect DSI interface of the display screen using 15PIN FPC cable.
We didn't use touch function, so we didn't connect 4pin (Without I2C connetion)

## 2. Software Setting

```shell
sudo apt install git
git clone https://github.com/waveshare/Waveshare-DSI-LCD
cd Waveshare-DSI-LCD/
# choose kernel your kernel verion
cd 6.1.21/
# choose your bits of your system (32 or 64)
cd 64/
# Install Driver
sudo bash ./WS_xinchDSI_MAIN.sh 79 I2C0
# Reload boot firmware by reboot
sudo reboot
```

## 3. Rotate Display

Display showed a vertical screen.

```shell
sudo nano /boot/cmdline.txt
```

Add following line at the beginning of the file.

```
video=DSI-1:400x1280M@60,rotate=90
```

Of course you can choose the angle. (0, 90, 180, 270)

```shell
sudo reboot
```

after adding rotation information, reboot RaspberryPi for check.

## 4. Rotate Display not worked

In our case, ‘video=DSI-1:400x1280**M@60**,rotate=90’ didn’t worked.
We modify ‘M@60’ to ‘e’, and it worked well.
So add following line at the beginning of the file.

```
video=DSI-1:400x1280**e**,rotate=90
```

```
video=DSI-1:400x1280e,rotate=90
```

## 5. Check Display

Check your display shows horizental CLI window.

## 6. Trouble shooting

If your system has some problem of initial boot or display, check that /boot/config.txt 

```shell
sudo nano /boot/config.txt
# If this file doesn’t have ‘dtoverlay=vc4-kms-v3d’, then add it.
```

There is a possibility of conflict if you use ‘kms’ and ‘fkms’ at the same time.
In our case, just using ‘dtoverlay=vc4-kms-v3d’ worked.
If this conflict occured, you can modify your config.txt by inserting SD card to your laptop.

---

### Reference

1. [Introduction Page of Display Manufacturer](https://www.waveshare.com/wiki/7.9inch_DSI_LCD#Method_1:_Install_Manually)
2. [Github Repository for Display Driver Installation](https://github.com/waveshare/Waveshare-DSI-LCD)
