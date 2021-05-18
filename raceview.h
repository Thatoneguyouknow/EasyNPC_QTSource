#ifndef RACEVIEW_H
#define RACEVIEW_H

#include <QWidget>
#include <QListWidgetItem>
#include <QTextStream>
#include "Attributes/Race.hpp"
#include "Attributes/Stats.hpp"
#include "newrace.h"

namespace Ui {
class raceview;
}

class raceview : public QWidget
{
    Q_OBJECT

public:
    explicit raceview(QWidget *parent = nullptr);
    ~raceview();
    void refreshRace();
    void newRace();

signals:
    void errorCaught(int err);

private:
    Ui::raceview *ui;
    newrace *edit;

private slots:
    void on_race_dc(QListWidgetItem *clicked);
    void onRefreshSignal();
};

static const int raceErr = 1106;

#endif // RACEVIEW_H
