#ifndef NEWRACE_H
#define NEWRACE_H

#include <QDialog>
#include <QAction>
#include <QTextStream>

#include "Attributes/stats.h"
#include "Attributes/race.h"
#include "Helper_Functions/errorlog.h"

namespace Ui {
class NewRace;
}

class NewRace : public QDialog
{
    Q_OBJECT

public:
    explicit NewRace(QWidget *parent = nullptr);
    explicit NewRace(int toEdit, QWidget *parent = nullptr);
    ~NewRace();

private:
    Ui::NewRace *ui;
    bool edit = false;
    int raceToEdit;

private slots:
    void save_clicked();
};

#endif // NEWRACE_H
