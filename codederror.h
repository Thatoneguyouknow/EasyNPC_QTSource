#ifndef CODEDERROR_H
#define CODEDERROR_H

#include <QDialog>
#include <QDesktopServices>
#include <QStandardPaths>
#include <QSysInfo>
#include <QTextStream>
#include <QUrl>

namespace Ui {
class CodedError;
}

class CodedError : public QDialog
{
    Q_OBJECT

public:
    explicit CodedError(int code, bool hasCode, QWidget *parent = nullptr);
    ~CodedError();

private:
    Ui::CodedError *ui;
    int errorCode;

private slots:
    void openReport();
};

#endif // CODEDERROR_H
