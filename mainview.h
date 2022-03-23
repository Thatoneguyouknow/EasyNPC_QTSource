#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "charcard.h"
#include "editchar.h"
#include "classcard.h"
#include "newclass.h"
#include "racecard.h"
#include "newrace.h"


class MainView : public QWidget
{
    Q_OBJECT
public:
    explicit MainView(QWidget *parent = nullptr);
    void show_chars();
    void show_class();
    void show_race();

    void display_char(int toDisp);
    void display_class(int toDisp = -1);
    void display_race(int toDisp = -1);

signals:
    void errorCaught(int err);

private:
    void createWindows();
    void createChCards();
    void createClCards();
    void createRCards();

    void refreshChars();
    void refreshClass();
    void refreshRace();

    QGridLayout* Recents;
    editchar *cEdit;
    NewClass *clEdit;
    NewRace *rEdit;

    map<int, CharCard*> chCards;
    map<int, ClassCard*> clCards;
    map<int, RaceCard*> rCards;

    QString emptyChar = "No Characters here. Make a new one by clicking New > Characters";
    QString emptyClass = "No Classes here. Make a new one by clicking New > Class";
    QString emptyRace = "No Races here. Make a new one by clicking New > Race";

private slots:
    void on_EditChar();
    void on_EditClass();
    void on_EditRace();

    void on_Refresh();

    void onError(int code);
};

const int CardErr = 1100;

#endif // MAINVIEW_H
