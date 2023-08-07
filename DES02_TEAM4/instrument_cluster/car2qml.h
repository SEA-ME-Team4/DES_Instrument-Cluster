#ifndef CAR2QML_H
#define CAR2QML_H

#include <QObject>
#include <QtDBus/QDBusInterface>
#include <QDBusReply>

class Car2Qml : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal speed READ getSpeed NOTIFY update2qml)
    Q_PROPERTY(qreal battery READ getBattery NOTIFY update2qml)
    Q_PROPERTY(qreal temp READ getTemp NOTIFY update2qml)
    Q_PROPERTY(bool brake READ getBrake NOTIFY update2qml)

public:
    explicit Car2Qml(QObject *parent = nullptr);
    Q_INVOKABLE qreal getSpeed();
    Q_INVOKABLE qreal getBattery();
    Q_INVOKABLE qreal getTemp();
    Q_INVOKABLE bool getBrake();

signals:
    Q_INVOKABLE void update2qml();
    Q_INVOKABLE void update2car();

public slots:
    Q_INVOKABLE void dbus_update();

private:
    QDBusInterface *dbus2car;
    QDBusReply<qreal> speed;
    QDBusReply<qreal> battery;
    QDBusReply<qreal> temp;
    QDBusReply<bool> brake;
};

#endif // CAR2QML_H
