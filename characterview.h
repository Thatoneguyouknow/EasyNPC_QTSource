#ifndef CHARACTERVIEW_H
#define CHARACTERVIEW_H

#include <QWidget>
#include "Generator.hpp"
#include "editchar.h"
#include <QListWidgetItem>

namespace Ui {
class CharacterView;
}

class CharacterView : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterView(QWidget *parent = nullptr);
    ~CharacterView();
    void addChar(Generator toAdd);
    void createChar();

private:
    Ui::CharacterView *ui;
    editChar *edit;
    void displayCharacter(int toDisp);
    void refreshList();

private slots:
    void on_object_dc(QListWidgetItem *clicked);
    void onRefreshSignal();
};

#endif // CHARACTERVIEW_H
