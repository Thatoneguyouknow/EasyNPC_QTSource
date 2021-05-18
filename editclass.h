#ifndef EDITCLASS_H
#define EDITCLASS_H

#include <QDialog>

namespace Ui {
class editClass;
}

class editClass : public QDialog
{
    Q_OBJECT

public:
    explicit editClass(QWidget *parent = nullptr);
    ~editClass();

private:
    Ui::editClass *ui;
};

#endif // EDITCLASS_H
