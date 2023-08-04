#include "instrumentcluster.h"
#include "ui_instrumentcluster.h"

InstrumentCluster::InstrumentCluster(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InstrumentCluster)
{
    ui->setupUi(this);
}

InstrumentCluster::~InstrumentCluster()
{
    delete ui;
}

