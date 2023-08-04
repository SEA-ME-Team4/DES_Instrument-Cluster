#include "instrumentcluster.h"
#include "ui_instrumentcluster.h"
#include <QDebug>

InstrumentCluster::InstrumentCluster(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InstrumentCluster)
    , carinfo("org.team4.Des02", "/CarInformation", "org.team4.Des02.CarInformation", QDBusConnection::sessionBus())
{
    ui->setupUi(this);
    ui->TestBlock->setEnabled(false);
    QTimer *timer = new QTimer(this);
    timer->start(1000.0f/60.0f);

    connect(timer, SIGNAL(timeout()), this, SLOT(gui_update()));
}

InstrumentCluster::~InstrumentCluster()
{
    delete ui;
}

void InstrumentCluster::gui_update()
{
    QDBusReply<qreal> temp = carinfo.call("getTemp");
    QString cvt_temp = QString::number(temp);
    ui->TestBlock->setText(cvt_temp);
    qDebug()<<cvt_temp;
}
