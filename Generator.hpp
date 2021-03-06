//
//  Generator.hpp
//  Dnd
//
//  Created by Benjamin Peterson on 1/22/21.
//

#ifndef Generator_hpp
#define Generator_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <QFile>
#include <QTextStream>
#include "Attributes/Class.hpp"
#include "Attributes/Race.hpp"
#include "Attributes/Stats.hpp"
#include "Attributes/Alignment.hpp"
#include "Helper_Functions/Personality.hpp"
#include "Helper_Functions/RaceNames.hpp"

using namespace std;

class Generator
{
public:
    Generator(bool empty=false);
    Generator(int id);
    Generator(const Generator &toCopy);
    ~Generator();
    
    // getters and setters
    int getGenID(bool setFlag=false, int toSet=-1);
    string getsetName(bool setFlag=false, string toSet="");
    int getsetRace(bool setFlag=false, int toSet=0);
    int getsetClass(bool setFlag=false, int toSet=0);
    // Alignment will be two integers between 0 and 2
    array<int, 2> getsetAlign(bool setFlag=false, array<int, 2> *toSet=nullptr);
    QString getsetPerson(bool setFlag=false, QString toSet="");
    int getsetLevel(bool setFlag=false, int toSet=0);
    array<int, 6> getsetStats(bool setFlag=false, array<int, 6>* toSet=nullptr);
    int getsetHP(bool setFlag=false, int toSet=0);
    QString getPersonTrait(int trait);
    
    string generateName();
    
private:
    // Objects
    int ID;
    string name;
    int race;
    int charClass;
    array<int, 2> alignment;
    QString personality;
    int level;
    array<int, 6> stats;
    int hp;
    
    // Functions
    int generateId();
    int generateRace();
    int generateClass();
    array<int, 2> generateAlign();
    QString generatePersonailty();
    int generateLevel();
    array<int, 6> generateStats(int cClass);
    int calculateHP(int charClass);

    int checkId(int id);
};

extern map<int, Generator>availableGens;
extern int nextGenID;

int rollStat();
void displayGenerator(Generator display);
void deleteGen(int toDel);

//SQL Function
int saveGens();
int saveGenerator(Generator toSave);
int sqlToGen(void* data, int argc, char** argv, char** azColName);
int readGenerators();
void removeAllFromSQL();
void removeFromSQL(Generator toRemove);

static const int GenCreateErr = 1117;
static const int gDbErr = 1201;
static const int genOpenErr = 1215;
static const int genFailPrep = 1216;
static const int genFailBind = 1217;
static const int genFailStep = 1218;
static const int genFailRead = 1219;

#endif /* Generator_hpp */
