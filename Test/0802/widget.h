#ifndef WIDGET_H
#define WIDGET_H

#include <QApplication>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QWidget>
#include <QTimer>
#include "car.h"
#include "car_adaptor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QDBusConnection connection = QDBusConnection::sessionBus();
public Q_SLOTS:
    void gui_update();

private:
    Ui::Widget *ui;
    QDBusInterface iface;
    QTimer *timer;
    Car *car = new Car();
};
#endif // WIDGET_H
