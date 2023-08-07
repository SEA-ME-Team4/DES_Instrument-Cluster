#include <QCoreApplication>
#include <QtDBus/QDBusConnection>

#include "carinformation.h"
#include "carinformation_adaptor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDBusConnection connection = QDBusConnection::sessionBus();
    CarInformation *carinfo = new CarInformation();
    new CarInformationAdaptor(carinfo);
    connection.registerObject("/CarInformation", carinfo);
    connection.registerService("org.team4.Des02");

    return a.exec();
}
