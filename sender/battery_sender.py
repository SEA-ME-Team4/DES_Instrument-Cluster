import dbus
import dbus.service

from piracer.vehicles import PiRacerStandard
from collections import deque

import time

def get_battery():
    voltage = piracer.get_battery_voltage() / 3
    # print(voltage)
    if(voltage>4.2):
        battery_percentage = 100
    elif(voltage>=4.1):
        battery_percentage = 87 + ((voltage-4.1)/(4.2-4.1))*(100-87)
    elif(voltage>=4.0):
        battery_percentage = 75 + ((voltage-4.0)/(4.1-4.0))*(87-75)
    elif(voltage>=3.9):
        battery_percentage = 55 + ((voltage-3.9)/(4.0-3.9))*(75-55)
    elif(voltage>=3.8):
        battery_percentage = 30 + ((voltage-3.8)/(3.9-3.8))*(55-30)
    elif(voltage>=3.6):
        battery_percentage = 0 + ((voltage-3.6)/(3.8-3.6))*(30-0)
    else:
        battery_percentage = 0  
       
        
    return battery_percentage


if __name__ == "__main__":
    piracer = PiRacerStandard()
    list = deque([0]*100)
    bus = dbus.SessionBus()
    service = bus.get_object("org.team4.Des02", "/CarInformation")
    car_interface = dbus.Interface(service, "org.team4.Des02.CarInformation")

    while 1:
        list.popleft()
        time_1 = time.time()
        now_battery = get_battery() 
        list.append(now_battery)
        battery = max(list)
        # print(float(battery))
        car_interface.setBattery(float(battery))
        time.sleep(0.01)
        time_2 = time.time()
        print("time: ", time_2 - time_1)
