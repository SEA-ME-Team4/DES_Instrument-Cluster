#include "carinformation.h"
CarInformation::CarInformation(QObject *parent) : QObject(parent)
{
    speed = 0.0;
    battery = 0.0;
    temp = 0.0;
    brake = false;

    speed_status = true;
    battery_status = true;
    temp_status = true;
    brake_status = true;

    speed_timer.start();
    battery_timer.start();
    temp_timer.start();
    brake_timer.start();

    system_timer = new QTimer(this);
    system_timer->start(1000.0f/120.0f);
    connect(system_timer, SIGNAL(timeout()), this, SLOT(onTimeSpend()));
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
    return speed;
}

qreal CarInformation::getBattery()
{
    return battery;
}

qreal CarInformation::getTemp()
{
    return temp;
}

bool CarInformation::getBrake()
{
    return brake;
}

bool CarInformation::getSpeedStatus()
{
    return speed_status;
}

bool CarInformation::getBatteryStatus()
{
    return battery_status;
}

bool CarInformation::getTempStatus()
{
    return temp_status;
}

bool CarInformation::getBrakeStatus(){
    return brake_status;
}

void CarInformation::onTimeSpend()
{
    if (speed_timer.elapsed()>MAX_INTERVAL && speed_status==false) {
        speed_status = true;
        emit speedTimeout(true);
    }
    else if (speed_timer.elapsed()<=MAX_INTERVAL && speed_status==true) {
        speed_status = false;
        emit speedTimeout(false);
    }

    if (battery_timer.elapsed()>MAX_INTERVAL && battery_status==false) {
        battery_status = true;
        emit batteryTimeout(true);
    }
    else if (battery_timer.elapsed()<=MAX_INTERVAL && battery_status==true) {
        battery_status = false;
        emit batteryTimeout(false);
    }

    if (temp_timer.elapsed()>MAX_INTERVAL && temp_status==false) {
        temp_status = true;
        emit tempTimeout(true);
    }
    else if (temp_timer.elapsed()<=MAX_INTERVAL && temp_status==true) {
        temp_status = false;
        emit tempTimeout(false);
    }

    if (brake_timer.elapsed()>MAX_INTERVAL && brake_status==false) {
        brake_status = true;
        emit brakeTimeout(true);
    }
    else if (brake_timer.elapsed()<=MAX_INTERVAL && brake_status==true) {
        brake_status = false;
        emit brakeTimeout(false);
    }

    emit sendTimeSpend();
}
