#ifndef NEWCLASS_H
#define NEWCLASS_H

#include <QDialog>
#include <QAction>
#include <QTextStream>
#include "Attributes/Stats.hpp"
#include "Attributes/Class.hpp"

namespace Ui {
class NewClass;
}

class NewClass : public QDialog
{
    Q_OBJECT

public:
    explicit NewClass(QWidget *parent = nullptr);
    explicit NewClass(int toEdit, QWidget *parent = nullptr);
    ~NewClass();
    int getEdit();

signals:
    void errorCaught(int err);

private:
    Ui::NewClass *ui;
    const QStringList hitdieStrs = {"d4", "d6", "d8", "d10", "d12", "d20"};
    bool edit = false;
    int classToEdit;

    void constructErr(int err);

private slots:
    void on_Save_clicked();
    void on_Delete_clicked();
};

static const int pListReadErr = 1105;

#endif // NEWCLASS_H
