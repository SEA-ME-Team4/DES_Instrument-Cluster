#ifndef CARINFORMATION_H
#define CARINFORMATION_H

#include <QObject>
#include <QElapsedTimer>
#include <QTimer>

#define MAX_INTERVAL 300

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

    bool getSpeedStatus();
    bool getBatteryStatus();
    bool getTempStatus();
    bool getBrakeStatus();

    void onTimeSpend();

signals:
    void sendTimeSpend();

    void speedTimeout(bool status);
    void batteryTimeout(bool status);
    void tempTimeout(bool status);
    void brakeTimeout(bool status);

private:
    QTimer *system_timer;

    QElapsedTimer speed_timer;
    QElapsedTimer battery_timer;
    QElapsedTimer temp_timer;
    QElapsedTimer brake_timer;

    bool speed_status;
    bool battery_status;
    bool temp_status;
    bool brake_status;

    float speed;
    float battery;
    float temp;
    bool brake;
};

#endif // CARINFORMATION_H
