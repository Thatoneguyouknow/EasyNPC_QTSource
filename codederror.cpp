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
        QString logPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        logPath.append("/error.log");
        ui->LogLabel->setText(logPath);
    }
}

CodedError::~CodedError()
{
    delete ui;
}

void CodedError::openReport()
{
    QDesktopServices::openUrl(QUrl::fromEncoded("https://github.com/Thatoneguyouknow/Dnd/issues"));
}
