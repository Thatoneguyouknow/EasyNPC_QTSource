#ifndef NEWRACE_H
#define NEWRACE_H

#include <QDialog>
#include <QAction>
#include <QTextStream>
#include "Attributes/Stats.hpp"
#include "Attributes/Race.hpp"

namespace Ui {
class newrace;
}

class newrace : public QDialog
{
    Q_OBJECT

public:
    explicit newrace(QWidget *parent = nullptr);
    explicit newrace(int toEdit, QWidget *parent = nullptr);
    ~newrace();

private:
    Ui::newrace *ui;
    bool edit = false;
    int raceToEdit;

private slots:
    void save_clicked();
};

#endif // NEWRACE_H
