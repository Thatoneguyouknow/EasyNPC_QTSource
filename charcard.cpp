#include "charcard.h"
#include "ui_charcard.h"

CharCard::CharCard(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharCard)
{
    ui->setupUi(this);
    Id = id;
    setUpWidget();
}

CharCard::~CharCard()
{
    delete ui;
}

void CharCard::setUpWidget()
{
    // On Name, Race, Class, Align setText() shorten longer strings and add "..." to the end.
    /*void check (QLabel *label)
    {
        QFontMetrics fm = label->fontMetrics();
        bool ok = fm.width(label->text()) <= label->width();
    }*/
    try {
        ui->Name->setText(QString::fromStdString(availableGens.at(Id).getsetName()));
        ui->Class->setText(QString::fromStdString(availableClasses.at(availableGens.at(Id).getsetClass()).getsetName()));
        ui->Race->setText(QString::fromStdString(availableRaces.at(availableGens.at(Id).getsetRace()).getsetName()));
    } catch(...) {
        QString error = "Card cannot be read: ";
        error.append(QString::number(Id));
        logError(genReadErr, error);
        emit errorCaught(genReadErr);

        // Set defaults "Jeff"
        ui->Name->setText("Jeff");
        ui->Class->setText("Jeff");
        ui->Race->setText("Jeff");
    }
    int bel;
    int mor;
    try {
        bel = availableGens.at(Id).getsetAlign().at(0);
        mor = availableGens.at(Id).getsetAlign().at(1);
        // catch align does not exist here
        if( bel == mor == 1 )
        {
            ui->Alignment->setText("True Neutral");
        }
        else
        {
            QString align = QString::fromStdString(belief.at(bel));
            align.append(QString::fromStdString(moral.at(mor)));
            ui->Alignment->setText(align);
        }
    }  catch (...) {
        QString error = "Alignment does not eixst: ";
        error.append(QString::number(bel));
        error.append(QString::number(mor));
        logError(alignExistErr, error);
        emit errorCaught(alignExistErr);

        // Set defaults "Lawful Good"
        ui->Alignment->setText("Lawful Good");
    }
    try {
        ui->StrVal->setText(QString::number(availableGens.at(Id).getsetStats().at(STRENGTH)));
        ui->DexVal->setText(QString::number(availableGens.at(Id).getsetStats().at(DEXTERITY)));
        ui->ConVal->setText(QString::number(availableGens.at(Id).getsetStats().at(CONSTITUTION)));
        ui->IntVal->setText(QString::number(availableGens.at(Id).getsetStats().at(INTELLIGENCE)));
        ui->WisVal->setText(QString::number(availableGens.at(Id).getsetStats().at(WISDOM)));
        ui->ChaVal->setText(QString::number(availableGens.at(Id).getsetStats().at(CHARISMA)));
    }  catch (...) {
        QString error = "Card cannot be read: ";
        error.append(QString::number(Id));
        logError(genReadErr, error);
        emit errorCaught(genReadErr);

        // Set defaults "8"
        ui->StrVal->setText(QString::number(8));
        ui->DexVal->setText(QString::number(8));
        ui->ConVal->setText(QString::number(8));
        ui->IntVal->setText(QString::number(8));
        ui->WisVal->setText(QString::number(8));
        ui->ChaVal->setText(QString::number(8));
    }
}

void CharCard::paintEvent(QPaintEvent *p2)
{
    try {
        QPixmap bkgnd(":/Images/Card.png");
        QPainter paint(this);
        paint.drawPixmap(-10, 0, 170, 170, bkgnd);
        QWidget::paintEvent(p2);
    }  catch (...) {
        QString error = "Image paint error";
        logError(paintErr, error);
        emit errorCaught(paintErr);
    }
}

