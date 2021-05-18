/********************************************************************************
** Form generated from reading UI file 'characterDisplay.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARACTERDISPLAY_H
#define UI_CHARACTERDISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CharacterDisplay
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *CharacterDisplay)
    {
        if (CharacterDisplay->objectName().isEmpty())
            CharacterDisplay->setObjectName(QString::fromUtf8("CharacterDisplay"));
        CharacterDisplay->resize(400, 300);
        gridLayoutWidget = new QWidget(CharacterDisplay);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(-1, -1, 401, 301));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(gridLayoutWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout->addWidget(listWidget, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout->addItem(verticalSpacer_2, 0, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);


        retranslateUi(CharacterDisplay);

        QMetaObject::connectSlotsByName(CharacterDisplay);
    } // setupUi

    void retranslateUi(QWidget *CharacterDisplay)
    {
        CharacterDisplay->setWindowTitle(QCoreApplication::translate("CharacterDisplay", "Form", nullptr));
        label->setText(QCoreApplication::translate("CharacterDisplay", "Characters", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CharacterDisplay: public Ui_CharacterDisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARACTERDISPLAY_H
