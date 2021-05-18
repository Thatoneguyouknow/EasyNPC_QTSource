//
//  Alignment.hpp
//  Dnd
//
//  Created by Benjamin Peterson on 1/22/21.
//
#ifndef Alignment_hpp
#define Alignment_hpp

#include <string>
#include "Helper_Functions/errorlog.h"
using namespace std;

const map<int, string> belief = {pair<int, string>(0, "Lawful "), pair<int, string>(1, "Neutral "), pair<int, string>(2, "Chaotic ")};
const map<int, string> moral = {pair<int, string>(0, "Good "), pair<int, string>(1, "Neutral "), pair<int, string>(2, "Evil ")};

#endif
