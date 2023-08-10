#ifndef CARINFORMATION_H
#define CARINFORMATION_H

#include <QObject>
#include <QElapsedTimer>
#include <QDebug>

#define MAX_INTERVAL 1000

class CarInformation : public QObject
{
    Q_OBJECT
public:
    explicit CarInformation(QObject *parent = nullptr);

public slots:
    void setSpeed(qreal speed);
    void setBattery(qreal battery);
    void setTemp(qreal temp);
    void setBrake(bool brake);

    qreal getSpeed();
    qreal getBattery();
    qreal getTemp();
    bool getBrake();

signals:
    void speedTimeout(bool status);
    void batteryTimeout(bool status);
    void tempTimeout(bool status);
    void brakeTimeout(bool status);

private:
    QElapsedTimer speed_timer;
    QElapsedTimer battery_timer;
    QElapsedTimer temp_timer;
    QElapsedTimer brake_timer;
    float speed;
    float battery;
    float temp;
    bool brake;
};

#endif // CARINFORMATION_H
