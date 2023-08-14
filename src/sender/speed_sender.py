import can
import dbus
import dbus.service

def receive_can_data():
    message = can_bus.recv()
    return message.data


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

    while 1:
      
        data = receive_can_data() 
        speed_data = get_speed_can(data)
        print(speed_data)
        car_interface.setSpeed(speed_data)
