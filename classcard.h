#ifndef CLASSCARD_H
#define CLASSCARD_H

#include <QWidget>
#include <QPixmap>
#include <QPalette>
#include <QBrush>
#include <QPainter>
#include <QTextStream>

#include "card.h"

#include "Attributes/class.h"
#include "newclass.h"
#include "Helper_Functions/errorlog.h"

namespace Ui {
class ClassCard;
}

class ClassCard : public QWidget, public Card
{
    Q_OBJECT

public:
    explicit ClassCard(int id, QWidget *parent = nullptr);
    ~ClassCard();

private:
    Ui::ClassCard *ui;
    void paintEvent(QPaintEvent *p2);
    void setUpWidget();

signals:
    void widgetClicked();
    void errorCaught(int err);

private slots:
    void mouseDoubleClickEvent(QMouseEvent *event)
    {
        emit widgetClicked();
    }
};

static const int cReadErr = 1118;

#endif // CLASSCARD_H
