# StartUp Shell Script

---

## 1. StartUp Program

- StartUp program makes our system shows instrument cluster and connect to D-Bus with senders when we just power on our PiRacer.
- For achieving this, at first, we use cron service. Because of some reasons(Frame Buffer initialization and D-Bus connection) we failed.
- So, we decied to use automatical source procedure of bash terminal. (bashrc)

---

## 2. startup.sh

```bash
#!/bin/bash --login

cluster_count=$(ps -ef | grep '/home/team4/des02/instrument_cluster' | wc -l)
if [ ${cluster_count} -eq 1 ];then
 echo instrument cluster on
 nohup /home/team4/des02/instrument_cluster -platform linuxfb &
fi

register_count=$(ps -ef | grep '/home/team4/des02/register_server' | wc -l)
if [ ${register_count} -eq 1 ];then
 echo register server on
 nohup /home/team4/des02/register_server &
fi

speed_count=$(ps -ef | grep 'python /home/team4/des02/speed_sender.py' | wc -l)
if [ ${speed_count} -eq 1 ];then
 echo speed sender on
 nohup python /home/team4/des02/speed_sender.py &
fi

brake_count=$(ps -ef | grep 'python /home/team4/des02/brake_sender.py' | wc -l)
if [ ${brake_count} -eq 1 ];then
 echo brake sender on
 nohup python /home/team4/des02/brake_sender.py &
fi

battery_count=$(ps -ef | grep 'python /home/team4/des02/battery_sender.py' | wc -l)
if [ ${battery_count} -eq 1 ];then
 echo battery sender on
 nohup python /home/team4/des02/battery_sender.py &
fi

gamepad_count=$(ps -ef | grep 'python /home/team4/des02/gamepad_control.py' | wc -l)
if [ ${gamepad_count} -eq 1 ];then
 echo gamepad on
 nohup python /home/team4/des02/gamepad_control.py &
fi
```

- If statement is for checking each process is already running or not.
- It prevents multiple running of application, because bashrc will read whenever you enter terminal (SSH also).
- nohup(no hang up) is used to run our application even if the session is disconnected.

---

## 3. killer.sh

```bash
var=$(ps -ef|grep $1|grep -v 'grep'|grep -v $0)
pid=$(echo ${var} | cut -d " " -f2)
 
if [ -n "${pid}" ]
then
    kill -9 ${pid}
    echo $* down.
 
else
    echo $* is not here.
fi
```

- Killer is for demonstration session. It kills service with excecution name.

---

## 4. bashrc

Add this line below of `.bashrc` for startup setting.

```bash
# After setting CAN and Virtual Environment for PiRacer
sh /home/team4/startup.sh
```

---

### Reference

1. [nohup](https://en.wikipedia.org/wiki/Nohup)
2. [bash & bashrc](https://wiki.ubuntuusers.de/Bash/bashrc/)