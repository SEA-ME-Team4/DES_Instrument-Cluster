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

    while (1) {
        if (connection.registerObject("/CarInformation", carinfo)){
            qDebug()<<"Register Object Success";
            break;
        }
        else {
            qDebug()<<"Register Object Failed";
        }
    }

    while (1) {
        if (connection.registerService("org.team4.Des02")){
            qDebug()<<"Register Service Success";
            break;
        }
        else {
            qDebug()<<"Register Service Failed";
        }
    }

    return a.exec();
}
