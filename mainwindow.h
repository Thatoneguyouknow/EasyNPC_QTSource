#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QMenuBar>
#include <QMessageBox>
#include <QSysInfo>
#include <QGridLayout>

#include "mainview.h"
#include "codederror.h"
#include "Database/database.h"
#include "Database/classsaver.h"
#include "Database/racesaver.h"
#include "Database/npcsaver.h"

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

    QGridLayout* Recents;
    MainView* RecentView;

    editchar *edit;

    QMenu* fileMenu;
    QMenu* newMenu;
    QMenu* helpMenu;

    QAction* newGen;
    QAction* newClass;
    QAction* newRace;
    QAction* refreshRaces;
    QAction* refreshClasses;
    QAction* reset;
    QAction* aboutAct;
    QAction* report;

    CodedError* errorDial;

    void newButtonActions(QMenu* menu);
    void menuActions();
    void createMenu();
    void createWindows();

private slots:
    void on_NEW_clicked();
    void on_NewChar();
    void on_NewClass();
    void on_NewRace();

    void on_Characters_clicked();
    void on_Classes_clicked();
    void on_Races_clicked();

    void onCRefresh();
    void onRRefresh();
    void onReset();
    void onCodedError(int code);
    void onUncodedError();
    void onAbout();
    void onQuit();
};

#endif // MAINWINDOW_H
