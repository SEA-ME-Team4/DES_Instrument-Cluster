#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QQuickView>

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr);
    Q_INVOKABLE int move();
    int a = 180;
signals:

};

#endif // TEST_H
