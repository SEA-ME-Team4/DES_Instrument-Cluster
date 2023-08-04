#ifndef INSTRUMENTCLUSTER_H
#define INSTRUMENTCLUSTER_H

#include <QWidget>
#include <QtDBus/QDBusInterface>
#include <QDBusReply>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class InstrumentCluster; }
QT_END_NAMESPACE

class InstrumentCluster : public QWidget
{
    Q_OBJECT

public:
    InstrumentCluster(QWidget *parent = nullptr);
    ~InstrumentCluster();

public Q_SLOTS:
    void gui_update();

private:
    Ui::InstrumentCluster *ui;
    QDBusInterface carinfo;
    QTimer *timer;
};
#endif // INSTRUMENTCLUSTER_H
