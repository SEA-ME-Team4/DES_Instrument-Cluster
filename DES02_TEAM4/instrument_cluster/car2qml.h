#ifndef CAR2QML_H
#define CAR2QML_H

#include <QObject>
#include <QElapsedTimer>
#include <QtDBus/QDBusInterface>
#include <QDBusReply>

class Car2Qml : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal speed READ getSpeed)
    Q_PROPERTY(qreal battery READ getBattery)
    Q_PROPERTY(qreal temp READ getTemp)
    Q_PROPERTY(bool brake READ getBrake)

public:
    explicit Car2Qml(QObject *parent = nullptr);

    qreal getSpeed();
    qreal getBattery();
    qreal getTemp();
    bool getBrake();

signals:
    void speedstatusChanged(bool status);
    void batterystatusChanged(bool status);
    void tempstatusChanged(bool status);
    void brakestatusChanged(bool status);


public slots:
    void setSpeed();
    void setBattery();
    void setTemp();
    void setBrake();

    void setSpeedStatus(bool status);
    void setBatteryStatus(bool status);
    void setTempStatus(bool status);
    void setBrakeStatus(bool status);

    Q_INVOKABLE void updateVariables();

private:
    QDBusInterface *interface;
    QDBusReply<qreal> speed;
    QDBusReply<qreal> battery;
    QDBusReply<qreal> temp;
    QDBusReply<bool> brake;


    bool speedstatus;
    bool batterystatus;
    bool tempstatus;
    bool brakestatus;
};

#endif // CAR2QML_H
