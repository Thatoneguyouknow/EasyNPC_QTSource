#ifndef CLASSVIEW_H
#define CLASSVIEW_H

#include <QWidget>
#include <QListWidgetItem>
#include <QTextStream>

#include "Attributes/class.h"
#include "newclass.h"
#include "Helper_Functions/errorlog.h"

namespace Ui {
class ClassView;
}

class ClassView : public QWidget
{
    Q_OBJECT

public:
    explicit ClassView(QWidget *parent = nullptr);
    ~ClassView();
    void refreshClassList();
    void newClass();

signals:
    void errorCaught(int err);

private:
    Ui::ClassView *ui;
    NewClass *edit;

private slots:
    void on_class_dc(QListWidgetItem *clicked);
    void onRefreshSignal();
    void onClassDelete();
    void recieveError(int err);
};

static const int displayErr = 1104;

#endif // CLASSVIEW_H
