//
//  Personality.cpp
//  Dnd
//
//  Created by Benjamin Peterson on 2/24/21.
//

#include "Personality.hpp"

int getNumLines(QString filename)
{
    QFile file(filename);
    if( !file.open(QFile::ReadOnly | QFile::Text))
    {
        // ErrorCode 1108
        QString error = "Cannot read file for lineNum: ";
        error.append(filename);
        logError(lineNumErr, error, getlogDir());
        return -1;
    }
    int lineCount = 0;
    QString line;
    QTextStream textIn(&file);

    while( textIn.readLineInto(&line))
    {
        lineCount++;
    }
    file.close();
    return lineCount;
}

QString getLineAt(QString fileName, int lineNum)
{
    QFile file(fileName);
    if( !file.open(QFile::ReadOnly | QFile::Text))
    {
        // ErrorCode 1109
        QString error = "Cannot read file for line: ";
        error.append(fileName);
        logError(lineReadErr, error, getlogDir());
        return "Error";
    }
    int lineCount = 0;
    QString line;
    QTextStream posIn(&file);

    while( posIn.readLineInto(&line) )
    {
        lineCount++;
        if(lineCount == lineNum)
        {
            file.close();
            return line;
        }
    }
    // ErrorCode 1110
    QString error = "Cannot find line: ";
    error.append(QString::number(lineNum));
    logError(lineFoundErr, error, getlogDir());
    return "Error";
}
