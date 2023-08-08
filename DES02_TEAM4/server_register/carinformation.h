#ifndef CARINFORMATION_H
#define CARINFORMATION_H

#include <QObject>

class CarInformation : public QObject
{
    Q_OBJECT
public:
    explicit CarInformation(QObject *parent = nullptr);

public Q_SLOTS:
    void setSpeed(qreal speed);
    void setBattery(qreal battery);
    void setTemp(qreal temp);
    void setBrake(bool brake);
    qreal getSpeed();
    qreal getBattery();
    qreal getTemp();
    bool getBrake();

private:
    float speed;
    float battery;
    float temp;
    bool brake;
};

#endif // CARINFORMATION_H
