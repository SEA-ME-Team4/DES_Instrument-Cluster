import dbus
import dbus.service
from piracer.vehicles import PiRacerStandard, PiRacerPro
from piracer.gamepads import ShanWanGamepad

if __name__ == '__main__':

    shanwan_gamepad = ShanWanGamepad()
    piracer = PiRacerStandard()

    bus = dbus.SessionBus()
    service = bus.get_object("org.team4.Des02", "/CarInformation")
    car_interface = dbus.Interface(service, "org.team4.Des02.CarInformation")


    while True:
        gamepad_input = shanwan_gamepad.read_data()

        left_value = gamepad_input.analog_stick_left.y

        # to ignore splashed value
        if -0.0038 > left_value > -0.0039:
            continue

        print(left_value)
        brake_status = False

        if left_value < 0:
            brake_status = True
        


        print(brake_status)
        car_interface.setBrake(brake_status)
