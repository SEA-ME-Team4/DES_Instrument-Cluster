#ifndef CAR2QML_H
#define CAR2QML_H

#include <QObject>
#include <QElapsedTimer>
#include <QtDBus/QDBusInterface>
#include <QDBusReply>
#include "carinformation_interface.h"

class Car2Qml : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal speed READ getSpeed)
    Q_PROPERTY(qreal battery READ getBattery)
    Q_PROPERTY(qreal temp READ getTemp)
    Q_PROPERTY(bool brake READ getBrake)

    Q_PROPERTY(bool speedstatus READ getSpeedStatus CONSTANT)
    Q_PROPERTY(bool batterystatus READ getBatteryStatus CONSTANT)
    Q_PROPERTY(bool tempstatus READ getTempStatus CONSTANT)
    Q_PROPERTY(bool brakestatus READ getBrakeStatus CONSTANT)

    Q_PROPERTY(bool dbusstatus READ getDbusStatus CONSTANT)

public:
    explicit Car2Qml(QObject *parent = nullptr);

    qreal getSpeed();
    qreal getBattery();
    qreal getTemp();
    bool getBrake();

    bool getSpeedStatus();
    bool getBatteryStatus();
    bool getTempStatus();
    bool getBrakeStatus();

    bool getDbusStatus();

signals:
    void speedChanged();
    void batteryChanged();
    void tempChanged();
    void brakeChanged();

    void speedstatusChanged(bool status);
    void batterystatusChanged(bool status);
    void tempstatusChanged(bool status);
    void brakestatusChanged(bool status);

    void dbusstatusChanged(bool status);

public slots:
    void setSpeed();
    void setBattery();
    void setTemp();
    void setBrake();

    void setSpeedStatus(bool status);
    void setBatteryStatus(bool status);
    void setTempStatus(bool status);
    void setBrakeStatus(bool status);

    void updateVariables();
    void checkDbusValid();

private:
    org::team4::Des02::CarInformation *interface;

    QTimer *app_timer;

    QDBusReply<qreal> speed;
    QDBusReply<qreal> battery;
    QDBusReply<qreal> temp;
    QDBusReply<bool> brake;

    bool speedstatus;
    bool batterystatus;
    bool tempstatus;
    bool brakestatus;

    bool dbusstatus;
};

#endif // CAR2QML_H
