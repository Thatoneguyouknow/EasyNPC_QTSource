#ifndef RACECARD_H
#define RACECARD_H

#include <QWidget>
#include <QPixmap>
#include <QPalette>
#include <QBrush>
#include <QPainter>
#include <QTextStream>

#include "card.h"

#include "Attributes/race.h"
#include "newrace.h"
#include "Helper_Functions/errorlog.h"

namespace Ui {
class RaceCard;
}

class RaceCard : public QWidget, public Card
{
    Q_OBJECT

public:
    explicit RaceCard(int id, QWidget *parent = nullptr);
    ~RaceCard();

private:
    Ui::RaceCard *ui;
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

static const int rReadErr = 1119;

#endif // RACECARD_H
