#include "car2qml.h"
#include <QDebug>
Car2Qml::Car2Qml(QObject *parent) : QObject(parent)
{
    dbus2car = new QDBusInterface("org.team4.Des02", "/CarInformation", "org.team4.Des02.CarInformation", QDBusConnection::sessionBus());
    dbus_update();
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

void Car2Qml::dbus_update()
{
    speed = dbus2car->call("getSpeed");
    battery = dbus2car->call("getBattery");
    temp = dbus2car->call("getTemp");
    brake = dbus2car->call("getBrake");
    emit update2car();
}
