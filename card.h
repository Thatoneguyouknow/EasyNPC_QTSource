#ifndef CARD_H
#define CARD_H

#include <QPaintEvent>

class Card
{
public:
    void refreshCard()
    {
        setUpWidget();
    }

    int getId()
    {
        return Id;
    }

protected:
    virtual void paintEvent(QPaintEvent *p2) = 0;
    virtual void setUpWidget() = 0;
    int Id;
};

#endif // CARD_H
