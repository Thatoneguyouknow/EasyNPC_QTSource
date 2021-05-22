#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QMenuBar>
#include <QMessageBox>
#include <QSysInfo>
#include <QGridLayout>

#include "classview.h"
#include "raceview.h"
#include "charcard.h"
#include "editchar.h"
#include "codederror.h"

#include "generator.h"
#include "Helper_Functions/errorlog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ClassView* cUi;
    RaceView* rUi;
    QGridLayout* Recents;

    editchar *edit;

    QMenu* fileMenu;
    QMenu* newMenu;
    QMenu* helpMenu;

    QAction* newGen;
    QAction* newClass;
    QAction* newRace;
    QAction* aboutAct;
    QAction* report;

    CodedError* errorDial;

    void newButtonActions(QMenu* menu);
    void menuActions();
    void createMenu();

    map<int, CharCard*> cards;

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
    void onAbout();
    void onQuit();
};

const int CardErr = 1100;
#endif // MAINWINDOW_H
