import can
import dbus
import dbus.service
from collections import deque

def receive_can_data():
    try:
        message = can_bus.recv(timeout=0.2)
        if message is not None:
            return message.data
        else:
            return None
    except can.CanError:
        return None


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

    # decord hexadecimal
    speed = (decimal_data_0*256)  + decimal_data_1 + (decimal_data_2*0.01)

    return speed


if __name__ == "__main__":

    can_interface = 'can1'  
    can_bus = can.interface.Bus(channel=can_interface, bustype='socketcan')    
    bus = dbus.SessionBus()
    service = bus.get_object("org.team4.Des02", "/CarInformation")
    car_interface = dbus.Interface(service, "org.team4.Des02.CarInformation")

    queue = deque([0]*4)

    while 1:
        # print(queue) 
        data = receive_can_data() 
        if data is not None:
            queue.popleft()
            speed_data = get_speed_can(data)
            queue.append(speed_data)

            ave_value = queue[0]*0.1 + queue[1]*0.2 + queue[2]*0.3 + queue[3]*0.4 
            print(speed_data)
            car_interface.setSpeed(ave_value)
        else:
            print("No CAN data recieved")