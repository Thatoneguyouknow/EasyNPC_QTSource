#ifndef EDITCHAR_H
#define EDITCHAR_H

#include <QDialog>
#include "generator.h"
#include "Helper_Functions/errorlog.h"

namespace Ui {
class editchar;
}

class editchar : public QDialog
{
    Q_OBJECT

public:
    explicit editchar(int toDisplay, QWidget *parent = nullptr);
    ~editchar();

signals:
    void errorCaught(int err);

private:
    Ui::editchar *ui;
    const vector<string> alignStrs =  {"Lawful Good", "Lawful Neutral", "Lawful Evil",\
                                       "Neutral Good", "True Neutral", "Neutral Evil",\
                                       "Chaotic Good", "Chaotic Neutral", "Chaotic Evil"};
    int generator;
    bool hasBeenEdited = false;

private slots:
    void onEdit();
    void onDelete();
    void onNewName();
    void onSave();
    void onOk();
};

static const int removeError = 1103;

#endif // EDITCHAR_H
