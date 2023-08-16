# Get Sender Data
## Table of Contents

### [Speed](#1-speed-data)

### [Battery](#2-battery-data)

### [Brake](#3-brake-data)

---

# 1. Speed Data

- When receiving message from CAN, We decode it and send it to Dbus.

- Install can package

```python
pip install python-can
```

### in `speed_sender.py`

- Connect with CAN bus

```python
can_interface = 'can1'  
can_bus = can.interface.Bus(channel=can_interface, bustype='socketcan')
```

- Receive can message by using `.recv` function.
- if CAN connection has error, the function returns `None`.

```python
def receive_can_data():
    try:
        message = can_bus.recv(timeout=0.2) # timeout 
        if message is not None:
            return message.data
        else:
            return None
    except can.CanError:
        return None
```

- Change `speed` byte to decimal, and decode it.

```python
def get_speed_can(data):
    # get data(index of 0, 1, 2)
    byte_0 = data[0]
    byte_1 = data[1]
    byte_2 = data[2]

    # change byte type to hexadecimal
    hex_data_0 = format(byte_0, '02X')
    hex_data_1 = format(byte_1, '02X')
    hex_data_2 = format(byte_2, '02X')

    # change hexadecimal to decimal
    decimal_data_0 = int(hex_data_0, 16)
    decimal_data_1 = int(hex_data_1, 16)
    decimal_data_2 = int(hex_data_2, 16)

    # decode hexadecimal
    speed = (decimal_data_0*256)  + decimal_data_1 + (decimal_data_2*0.01)

    return speed
```

## Data processing

- Import deque

```python
from collections import deque
```

- Declare deque(size: 4)

```python
queue = deque([0]*4)
```

- In order to follow the most recent speed while reducing noise, weight was given based on the order in which data came into the queue.
- And send the `ave_value` to Dbus.

```python
while 1:
        data = receive_can_data() 
        if data is not None:
            queue.popleft()
            speed_data = get_speed_can(data)
            queue.append(speed_data)

            ave_value = queue[0]*0.1 + queue[1]*0.2 + queue[2]*0.3 + queue[3]*0.4
            print(speed_data)
            car_interface.setSpeed(ave_value) # send data to Dbus
        else:
            print("No CAN data recieved")
```

---

# 2. Battery Data

- We used `get_battery_voltage` function which is placed in `piracer` package.
- By using it in `battery_sender.py`, we made a function which can calculate battery_percentage.

```python
from piracer.vehicles import PiRacerStandard

def get_battery():
    voltage = piracer.get_battery_voltage() / 3
    print(voltage)
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
        return voltage

		return battery_percentage
```

## How to calculate battery percentage

- We got an information about voltage state of charge of lithium battery from an [official website](https://www.akkushop.de/de/3400mah-panasonic-18650-li-ion-akku-mit-eigener-schutzschaltung-ca.-69-x-1861mm-beachten/?gclid=Cj0KCQjw2eilBhCCARIsAG0Pf8vO9KMf3kPwGwAs5B6yAVukp_r2XorosHUAIDuSco5hoI0us5uJWfsaAjxJEALw_wcB).

<img width="610" alt="Untitled (11)" src="https://github.com/SEA-ME/SEA-ME-course-book/assets/106136905/272a8a9f-8d55-4154-8abe-ffe0df86340a">

- With this information, we made a function by using linear interpolation.

<img width="349" alt="Untitled (12)" src="https://github.com/SEA-ME/SEA-ME-course-book/assets/106136905/a57a58e5-898a-4223-a9e4-980ea8733bd2">

## Data processing

- Battery data wasn’t stable, so we collected maximum value to reduce noise data of battery.

### in `battey_sender.py`

- Import deque

```python
from collections import deque
```

- Declare deque (size: 100)

```python
list = deque([0]*100)
```

- Whenever new data comes in to `list`, remove first data and append new data.
- And then, send maximum data of list to Dbus.

```python
while 1:
        list.popleft() # remove first data
        now_battery = get_battery() 
        list.append(now_battery) # append new data
        battery = max(list) 
        car_interface.setBattery(float(battery)) # send data to Dbus
```

---

# 3. Brake Data

- We used `shawan_gamepad.read_data()` function which is also placed in `piracer` package.
- When left stick is manipulated, it returns the data by variable of `brake`.
- But it only gets data when the left stick is manipulated, so if you keep holding the stick, It cannot get data and waits for next manipuliate.
- `timeout` decorator is added for preventing long wait for next manipuliation.

### in `brake_sender.py`

```python
@timeout(0.01)
def getBrake():
    gamepad_input = shanwan_gamepad.read_data()
    brake = gamepad_input.analog_stick_left.y
    return brake
```

- If `gamepad_input`’s value is less than -0.0038758507034516434, that is, when you’re controlling the backwards, send `True` to Dbus
(Because in stable position, `gamepad_input` is - 0.0038758507034516434)
- else, send `False` to Dbus

```python
while True:
        try:
            gamepad_input = getBrake()
        except:
            pass
        if gamepad_input < -0.0038758507034516434: # to ignore splashing value
            print("brake")
            car_interface.setBrake(True) # send data to Dbus
        else:
            print("NO brake")
            car_interface.setBrake(False) # send data to Dbus
```
