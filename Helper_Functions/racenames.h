#ifndef RACENAMES_H
#define RACENAMES_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

#include <QString>

#include "Helper_Functions/errorlog.h"

using namespace std;

typedef string (*fn)();

string createName(int race);
void createMap();

extern map<int, string(*)()> raceName;

static const int createErr = 1107;
#endif // RACENAMES_H
