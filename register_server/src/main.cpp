#include <QCoreApplication>
#include <QtDBus/QDBusConnection>
#include <QDebug>

#include "carinformation.h"
#include "carinformation_adaptor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDBusConnection connection = QDBusConnection::sessionBus();
    CarInformation *carinfo = new CarInformation();
    new CarInformationAdaptor(carinfo);

    if (connection.registerObject("/CarInformation", carinfo)){
        qDebug()<<"Register Object Success";
    }
    else {
        qDebug()<<"Register Object Failed";
    }
    if (connection.registerService("org.team4.Des02")){
        qDebug()<<"Register Service Success";
    }
    else {
        qDebug()<<"Register Service Failed";
    }


    return a.exec();
}
