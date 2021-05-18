//
//  RaceNames.hpp
//  dnd_gui
//
//  Created by Benjamin Peterson on 3/17/21.
//

#ifndef RaceNames_hpp
#define RaceNames_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include "Helper_Functions/errorlog.h"

using namespace std;

typedef string (*fn)();

string createName(int race);

void createMap();

extern map<int, string(*)()> raceName;

static const int createErr = 1107;
#endif /* RaceNames_hpp */
