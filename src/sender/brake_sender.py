from piracer.gamepads import ShanWanGamepad
import dbus
import dbus.service

from functools import wraps
import errno
import os
import signal
import time


class TimeoutError(Exception):
    pass

def timeout(seconds, error_message=os.strerror(errno.ETIME)):
    def decorator(func):
        def _handle_timeout(signum, frame):
            raise TimeoutError(error_message)

        def wrapper(*args, **kwargs):
            signal.signal(signal.SIGALRM, _handle_timeout)
            signal.setitimer(signal.ITIMER_REAL,seconds) #used timer instead of alarm
            try:
                result = func(*args, **kwargs)
            finally:
                signal.alarm(0)
            return result
        return wraps(func)(wrapper)
    return decorator

@timeout(0.01)
def getBrake():
    gamepad_input = shanwan_gamepad.read_data()
    brake = gamepad_input.analog_stick_left.y
    return brake
    
if __name__ == '__main__':
    bus = dbus.SessionBus()
    service = bus.get_object("org.team4.Des02", "/CarInformation")
    car_interface = dbus.Interface(service, "org.team4.Des02.CarInformation")
    shanwan_gamepad = ShanWanGamepad()
    
    gamepad_input = 0
    value = 0

    while True:
        try:
            gamepad_input = getBrake()
        except:
            pass
        if gamepad_input < -0.0038758507034516434:
            print("brake")
            car_interface.setBrake(True)
        else:
            print("NO brake")
            car_interface.setBrake(False)
        time.sleep(0.05)

