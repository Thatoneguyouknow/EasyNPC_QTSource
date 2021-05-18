//
//  Stats.hpp
//  Dnd
//
//  Created by Benjamin Peterson on 1/22/21.
//
#ifndef Stats_hpp
#define Stats_hpp

#include <map>
#include <string>
#include <array>
#include "Helper_Functions/errorlog.h"
using namespace std;

enum stats {STRENGTH, DEXTERITY, CONSTITUTION, INTELLIGENCE, WISDOM, CHARISMA};
// Should these be static?
const map<int, string> statNames = {pair<int, string>(STRENGTH, "Strength"), pair<int, string>(DEXTERITY, "Dexterity"), pair<int, string>(CONSTITUTION, "Constitution"), pair<int, string>(INTELLIGENCE, "Intelligence"), pair<int, string>(WISDOM, "Wisdom"), pair<int, string>(CHARISMA, "Charisma")};
const map<int, string> abbvStat = {pair<int, string>(STRENGTH, "Str"), pair<int, string>(DEXTERITY, "Dex"), pair<int, string>(CONSTITUTION, "Con"), pair<int, string>(INTELLIGENCE, "Int"), pair<int, string>(WISDOM, "Wis"), pair<int, string>(CHARISMA, "Cha")};
const map<int, string> hitdieVals = {pair<int, string>(4, "d4"), pair<int, string>(6, "d6"), pair<int, string>(8, "d8"), pair<int, string>(10, "d10"), pair<int, string>(12, "d12"), pair<int, string>(20, "d20")};
const array<int, 6> hdNums = {4, 6, 8, 10, 12, 20};

int calcModifier(int abilityScore);
int searchStats(string stat);
int searchHd(string hit);
int getHdPos(int HitDie);

static const int statNotFound = 1111;
static const int hdNotFound = 1112;
static const int hdPosNotFound = 1113;
#endif
