#include "codederror.h"
#include "ui_codederror.h"

CodedError::CodedError(int code, bool hasCode, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CodedError)
{
    ui->setupUi(this);

    if(hasCode)
    {
       errorCode = code;
       ui->Code->setText(QString::number(errorCode));
    }
    else
    {
        ui->Code->hide();
    }

    QString os = QSysInfo::productType();
    if( os.contains("osx") || os.contains("mac") )
    {
        ui->LogLabel->setText("~/Library/Application Support/EasyNPC/error.log");
    }
    else
    {
        ui->LogLabel->setText("Windows DIR");
    }
}

CodedError::~CodedError()
{
    delete ui;
}

void CodedError::openReport()
{
    // Generate copy of data.db to log.db in an easy-to-retrieve log folder
    /*ui->Code->hide();
    ui->Reject->hide();
    ui->Report->hide();
    ui->label->hide();
    ui->label_2->hide();*/

    /*QString toSend = " Please email\n EasyNPC@protonmail.com the following: \n\n   Subject:  EasyNPC error ";
    toSend.append(errorCode);
    toSend.append("\n\n   Body: Error occurred on ");

    QString os = QSysInfo::productType();
    QString location;
    if( os.contains("osx") || os.contains("mac") )
    {
        os = "MacOS";
        location = "\\Applications\\EasyNPC\\Contents\\MacOS\\data.db";
    }
    else
    {
        os = "Windows OS";
        location = "Bruh";
    }
    toSend.append(os);
    toSend.append("\n\n Please attach the following file to your email:\n");
    toSend.append(location);

    QLabel* email = new QLabel(this);
    email->setText(toSend);
    email->show();*/
    QDesktopServices::openUrl(QUrl::fromEncoded("https://github.com/Thatoneguyouknow/Dnd/issues"));
    //QWidget::close();
}
