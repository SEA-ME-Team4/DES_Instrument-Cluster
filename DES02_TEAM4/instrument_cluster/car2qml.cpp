#include "car2qml.h"
#include <QDebug>

Car2Qml::Car2Qml(QObject *parent) : QObject(parent)
{
    interface = new QDBusInterface("org.team4.Des02", "/CarInformation", "org.team4.Des02.CarInformation", QDBusConnection::sessionBus());

    speedstatus = false;
    batterystatus = false;
    tempstatus = false;
    brakestatus = false;

    connect(interface, SIGNAL(speedTimeout(bool)), this, SLOT(setSpeedStatus(bool)));
    connect(interface, SIGNAL(batteryTimeout(bool)), this, SLOT(setBatteryStatus(bool)));
    connect(interface, SIGNAL(tempTimeout(bool)), this, SLOT(setTempStatus(bool)));
    connect(interface, SIGNAL(brakeTimeout(bool)), this, SLOT(setBrakeStatus(bool)));
}

void Car2Qml::setSpeed()
{
    speed = interface->call("getSpeed");
}

void Car2Qml::setBattery()
{
    battery = interface->call("getBattery");
}

void Car2Qml::setTemp()
{
    temp = interface->call("getTemp");
}

void Car2Qml::setBrake()
{
    brake = interface->call("getBrake");
}

void Car2Qml::setSpeedStatus(bool status)
{
    speedstatus = status;
    emit speedstatusChanged(status);
}

void Car2Qml::setBatteryStatus(bool status)
{
    batterystatus = status;
    emit batterystatusChanged(status);
}

void Car2Qml::setTempStatus(bool status)
{
    tempstatus = status;
    emit tempstatusChanged(status);
}

void Car2Qml::setBrakeStatus(bool status)
{
    brakestatus = status;
    emit brakestatusChanged(status);
}

qreal Car2Qml::getSpeed()
{
    return speed;
}

qreal Car2Qml::getBattery()
{
    return battery;
}

qreal Car2Qml::getTemp()
{
    return temp;
}

bool Car2Qml::getBrake()
{
    return brake;
}

void Car2Qml::updateVariables()
{
    setSpeed();
    setBattery();
    setTemp();
    setBrake();
}
