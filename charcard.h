#ifndef CHARCARD_H
#define CHARCARD_H

#include <QWidget>
#include <QPixmap>
#include <QPalette>
#include <QBrush>
#include <QPainter>
#include <QTextStream>

#include "card.h"

#include "generator.h"
#include "editchar.h"
#include "Helper_Functions/errorlog.h"

namespace Ui {
class CharCard;
}

class CharCard : public QWidget, public Card
{
    Q_OBJECT

public:
    explicit CharCard(int id, QWidget *parent = nullptr);
    ~CharCard();

private:
    Ui::CharCard *ui;
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

static const int genReadErr = 1101;
static const int alignExistErr = 1114;

#endif // CHARCARD_H
