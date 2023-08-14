#include "car2qml.h"
#include <QDebug>

Car2Qml::Car2Qml(QObject *parent) : QObject(parent)
{
    interface = new org::team4::Des02::CarInformation("org.team4.Des02", "/CarInformation", QDBusConnection::sessionBus());

    connect(interface, SIGNAL(speedTimeout(bool)), this, SLOT(setSpeedStatus(bool)));
    connect(interface, SIGNAL(batteryTimeout(bool)), this, SLOT(setBatteryStatus(bool)));
    connect(interface, SIGNAL(tempTimeout(bool)), this, SLOT(setTempStatus(bool)));
    connect(interface, SIGNAL(brakeTimeout(bool)), this, SLOT(setBrakeStatus(bool)));

    connect(interface, SIGNAL(sendTimeSpend()), this, SLOT(updateVariables()));

    dbusstatus = true;
    app_timer = new QTimer(this);
    app_timer->start(1000);
    connect(app_timer, SIGNAL(timeout()), this, SLOT(checkDbusValid()));
}

void Car2Qml::setSpeed()
{
    speed = interface->call("getSpeed");
    emit speedChanged();
}

void Car2Qml::setBattery()
{
    battery = interface->call("getBattery");
    emit batteryChanged();
}

void Car2Qml::setTemp()
{
    temp = interface->call("getTemp");
    emit tempChanged();
}

void Car2Qml::setBrake()
{
    brake = interface->call("getBrake");
    emit brakeChanged();
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

bool Car2Qml::getSpeedStatus()
{
    speedstatus = interface->call("getSpeedStatus").arguments()[0].toBool();
    return speedstatus;
}

bool Car2Qml::getBatteryStatus()
{
    batterystatus = interface->call("getBatteryStatus").arguments()[0].toBool();
    return batterystatus;
}

bool Car2Qml::getTempStatus()
{
    tempstatus = interface->call("getTempStatus").arguments()[0].toBool();
    return tempstatus;
}

bool Car2Qml::getBrakeStatus()
{
    brakestatus = interface->call("getBrakeStatus").arguments()[0].toBool();
    return brakestatus;
}

bool Car2Qml::getDbusStatus()
{
    checkDbusValid();
    return dbusstatus;
}

void Car2Qml::updateVariables()
{
    setSpeed();
    setBattery();
    setTemp();
    setBrake();
}

void Car2Qml::checkDbusValid()
{
    if (!interface->isValid() && dbusstatus==false) {
        dbusstatus = true;
        emit dbusstatusChanged(true);
    }
    else if (interface->isValid() && dbusstatus==true) {
        dbusstatus = false;
        emit dbusstatusChanged(false);
    }
}
