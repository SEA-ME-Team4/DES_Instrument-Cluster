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
