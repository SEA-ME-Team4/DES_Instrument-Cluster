#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    timer->start(1000.0f/60.0f);
    ui->pushButton->setEnabled(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(gui_update()));
}

Widget::~Widget()
{
    delete ui;
}
void Widget::gui_update()
{
    if (a<=2)
    {
        ui->pushButton->setEnabled(true);
    }
    else if (a<=4)
    {
        ui->pushButton->setEnabled(false);
    }
    if (a==5)
    {
        a=1;
    }
    a = a+1;
}
