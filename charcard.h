#ifndef CHARCARD_H
#define CHARCARD_H

#include <QWidget>
#include <QPixmap>
#include <QPalette>
#include <QBrush>
#include <QPainter>
#include <QTextStream>
#include "Generator.hpp"
#include "editchar.h"

namespace Ui {
class CharCard;
}

class CharCard : public QWidget
{
    Q_OBJECT

public:
    explicit CharCard(int id, QWidget *parent = nullptr);
    ~CharCard();

    void refreshCard();
    int getId();

signals:
    void widgetClicked();
    void errorCaught(int err);

private:
    Ui::CharCard *ui;
    int charId;
    editChar *edit;

    void setUpWidget();


private slots:
    void mouseDoubleClickEvent(QMouseEvent *event);

protected:
    void paintEvent(QPaintEvent *p2);
};

static const int genReadErr = 1101;
static const int paintErr = 1102;
static const int alignExistErr = 1114;

#endif // CHARCARD_H
