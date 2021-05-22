#ifndef PERSONALITY_H
#define PERSONALITY_H

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

#include <QTextStream>
#include <QFile>
#include <QString>

#include "Helper_Functions/errorlog.h"

using namespace std;

int getNumLines(QString fileName);
QString getLineAt(QString fileName, int lineNum);

static const int lineNumErr = 1108;
static const int lineReadErr = 1109;
static const int lineFoundErr = 1110;
#endif // PERSONALITY_H
