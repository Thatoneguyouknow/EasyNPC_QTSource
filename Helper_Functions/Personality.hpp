//
//  Personality.hpp
//  Dnd
//
//  Created by Benjamin Peterson on 2/24/21.
//

#ifndef Personality_hpp
#define Personality_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <QTextStream>
#include <QFile>
#include "Helper_Functions/errorlog.h"

using namespace std;

int getNumLines(QString fileName);
QString getLineAt(QString fileName, int lineNum);

static const int lineNumErr = 1108;
static const int lineReadErr = 1109;
static const int lineFoundErr = 1110;

#endif /* Personality_hpp */
