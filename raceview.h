#ifndef RACEVIEW_H
#define RACEVIEW_H

#include <QWidget>
#include <QListWidgetItem>
#include <QTextStream>

#include "Attributes/race.h"
#include "Attributes/stats.h"
#include "Helper_Functions/errorlog.h"

#include "newrace.h"

namespace Ui {
class RaceView;
}

class RaceView : public QWidget
{
    Q_OBJECT

public:
    explicit RaceView(QWidget *parent = nullptr);
    ~RaceView();
    void refreshRace();
    void newRace();

signals:
    void errorCaught(int err);

private:
    Ui::RaceView *ui;
    NewRace *edit;

private slots:
    void on_race_dc(QListWidgetItem *clicked);
    void onRefreshSignal();

};

static const int raceErr = 1106;

#endif // RACEVIEW_H
