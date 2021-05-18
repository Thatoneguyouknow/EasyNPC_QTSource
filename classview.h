#ifndef CLASSVIEW_H
#define CLASSVIEW_H

#include <QWidget>
#include "Attributes/Class.hpp"
#include "newclass.h"
#include <QListWidgetItem>
#include <QTextStream>

namespace Ui {
class classview;
}

class classview : public QWidget
{
    Q_OBJECT

public:
    explicit classview(QWidget *parent = nullptr);
    ~classview();
    void refreshClassList();
    void newClass();

signals:
    void errorCaught(int err);

private:
    Ui::classview *ui;
    NewClass *edit;

private slots:
    void on_class_dc(QListWidgetItem *clicked);
    void onRefreshSignal();
    void onClassDelete();
    void recieveError(int err);
};

static const int displayErr = 1104;

#endif // CLASSVIEW_H
