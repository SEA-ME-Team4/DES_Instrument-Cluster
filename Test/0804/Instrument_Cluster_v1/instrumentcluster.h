#ifndef INSTRUMENTCLUSTER_H
#define INSTRUMENTCLUSTER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class InstrumentCluster; }
QT_END_NAMESPACE

class InstrumentCluster : public QWidget
{
    Q_OBJECT

public:
    InstrumentCluster(QWidget *parent = nullptr);
    ~InstrumentCluster();

private:
    Ui::InstrumentCluster *ui;
};
#endif // INSTRUMENTCLUSTER_H
