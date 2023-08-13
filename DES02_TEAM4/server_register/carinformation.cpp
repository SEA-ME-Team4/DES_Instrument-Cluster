#include "carinformation.h"
CarInformation::CarInformation(QObject *parent) : QObject(parent)
{
    speed = 0.0;
    battery = 0.0;
    temp = 0.0;
    brake = false;

    speed_timer.start();
    battery_timer.start();
    temp_timer.start();
    brake_timer.start();
}

void CarInformation::setSpeed(qreal speed)
{
    this->speed = speed;
    speed_timer.restart();
}

void CarInformation::setBattery(qreal battery)
{
    this->battery = battery;
    battery_timer.restart();
}

void CarInformation::setTemp(qreal temp)
{
    this->temp = temp;
    temp_timer.restart();
}

void CarInformation::setBrake(bool brake)
{
    this->brake = brake;
    brake_timer.restart();
}

qreal CarInformation::getSpeed()
{
    if (speed_timer.elapsed()>MAX_INTERVAL) {
        emit speedTimeout(true);
        qDebug()<<"Speed Update TIMEOUT (over MAXIMUM INTERVAL)";
    }
    else{
        emit speedTimeout(false);
    }
    return speed;
}

qreal CarInformation::getBattery()
{
    if (battery_timer.elapsed()>MAX_INTERVAL) {
        emit batteryTimeout(true);
        qDebug()<<"Battery Update TIMEOUT (over MAXIMUM INTERVAL)";
    }
    else{
        emit batteryTimeout(false);
    }
    return battery;
}

qreal CarInformation::getTemp()
{
    if (temp_timer.elapsed()>MAX_INTERVAL) {
        emit tempTimeout(true);
//        qDebug()<<"Temp Update TIMEOUT (over MAXIMUM INTERVAL)";
    }
    else{
        emit tempTimeout(false);
    }
    return temp;
}

bool CarInformation::getBrake()
{
    if (brake_timer.elapsed()>MAX_INTERVAL) {
        emit brakeTimeout(true);
//        qDebug()<<"Brake Update TIMEOUT (over MAXIMUM INTERVAL)";
    }
    else{
        emit brakeTimeout(false);
    }
    return brake;
}
