#ifndef CAR_H
#define CAR_H

#include <QObject>

class Car : public QObject
{
    Q_OBJECT
public:
    explicit Car(QObject *parent = nullptr);

public Q_SLOTS:
    void setSpeed(qreal speed);
    void setBattery(qreal battery);
    void setTemp(qreal temp);
    qreal getSpeed();
    qreal getBattery();
    qreal getTemp();

//Q_SIGNALS:
//    Q_SCRIPTABLE qreal blabla();

private:
    float speed;
    float battery;
    float temp;
};

#endif // CAR_H
