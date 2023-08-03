#include "car.h"
Car::Car(QObject *parent) : QObject(parent)
{
    speed = 0.0;
    battery = 100.0;
    temp = 50.0;
}

void Car::setSpeed(qreal speed)
{
    this->speed = speed;
}
void Car::setBattery(qreal battery)
{
    this->battery = battery;
}
void Car::setTemp(qreal temp)
{
    this->temp = temp;
}

qreal Car::getSpeed()
{
    return speed;
}
qreal Car::getBattery()
{
    return battery;
}
qreal Car::getTemp()
{
    return temp;
}
