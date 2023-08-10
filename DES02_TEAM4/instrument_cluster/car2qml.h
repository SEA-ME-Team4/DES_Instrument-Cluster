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

    Q_PROPERTY(bool speedstatus READ getSpeedStatus)
    Q_PROPERTY(bool batterystatus READ getBatteryStatus)
    Q_PROPERTY(bool tempstatus READ getTempStatus)
    Q_PROPERTY(bool brakestatus READ getBrakeStatus)

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
