#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QMenuBar>
#include <QMessageBox>
#include <QSysInfo>
#include "ui_mainwindow.h"
#include "characterview.h"
#include "charcard.h"
#include "classview.h"
#include "raceview.h"
#include "newclass.h"
#include "newrace.h"
#include "Generator.hpp"
#include "editchar.h"
#include "codederror.h"
#include "Helper_Functions/errorlog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void on_NEW_clicked();
    void on_NewChar();
    void on_NewClass();
    void on_NewRace();
    void on_EditChar();
    void on_Characters_clicked();
    void on_Classes_clicked();
    void on_Races_clicked();
    void onCharRefresh();
    void onCharDel();
    void onCodedError(int code);
    void onUncodedError();
    void onQuit();
    void onAbout();

private:
    Ui::MainWindow ui;

    editChar* edit;
    classview* cUi;
    raceview* rUi;
    NewClass* cnew;
    newrace* rnew;
    QGridLayout* Recents;

    QMenu* fileMenu;
    QMenu* newMenu;
    QMenu* helpMenu;
    QAction* newGen;
    QAction* newClass;
    QAction* newRace;
    QAction* aboutAct;
    QAction* report;

    QString os;

    CodedError* errorDial;

    void newButtonActions(QMenu* menu);
    void menuActions();
    void createMenu();

    map<int, CharCard*> cards;

};

const int CardErr = 1100;

#endif // MAINWINDOW_H
