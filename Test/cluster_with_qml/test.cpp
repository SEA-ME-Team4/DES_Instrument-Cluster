#include "test.h"

Test::Test(QObject *parent) : QObject(parent)
{
    qmlRegisterType<Test>("testinfo", 1, 0, "Test");
}

int Test::move()
{
    if (a>100){
        a = 0;
    }
    a++;
    return a;
}
