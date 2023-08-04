#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , iface("org.team4.Des", "/org/team4/DES/Car", "org.team4.Des.CarInformation", QDBusConnection::sessionBus())
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    timer->start(1000.0f/60.0f);

    new CarInformationAdaptor(car);
    connection.registerObject("/org/team4/DES/Car", car);
    connection.registerService("org.team4.des");

    connect(timer, SIGNAL(timeout()), this, SLOT(gui_update()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::gui_update()
{
//    return;
    QDBusReply<qreal> a = iface.call("getTemp");
    qDebug()<<a.value();
//    qDebug()<<car->getTemp();
}
