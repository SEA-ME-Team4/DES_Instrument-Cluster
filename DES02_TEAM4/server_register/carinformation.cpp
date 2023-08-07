#include "carinformation.h"
CarInformation::CarInformation(QObject *parent) : QObject(parent)
{
    speed = 0.0;
    battery = 100.0;
    temp = 50.0;
    brake = false;
}

void CarInformation::setSpeed(qreal speed)
{
    this->speed = speed;
}
void CarInformation::setBattery(qreal battery)
{
    this->battery = battery;
}
void CarInformation::setTemp(qreal temp)
{
    this->temp = temp;
}

void CarInformation::setBrake(bool brake)
{
    this->brake = brake;
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
