//
//  Class.hpp
//  Dnd
//
//  Created by Benjamin Peterson on 1/21/21.
//

#ifndef Class_hpp
#define Class_hpp

#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <sqlite3.h>
#include "Stats.hpp"
#include "Helper_Functions/Database.hpp"
#include <array>

using namespace std;

class Class
{
public:
    Class(bool empty=true);
    Class(string name, int hitdie, array<int, 6> priority, int userMade);
    Class(const Class &toCopy);
    ~Class();
    Class& operator=(const Class& other)
    {
        if( this != &other )
        {
            classID = other.classID;
            name = other.name;
            hitDie = other.hitDie;
            statPriority = other.statPriority;
            userCreated = other.userCreated;
        }
        return *this;
    }
    
    string getsetName(bool setFlag=false, string toSet="");
    int getsetHitDie(bool setFlag=false, int toSet=0);
    int getClassID();
    array<int, 6> getsetPriority(bool setFlag=false, array<int, 6> *toSet=nullptr);
    int getsetUser(bool setFlag=false, int toSet=0);
    
private:
    int classID;
    string name;
    int userCreated;
    // this number will be what kind of die is used to roll (d12, d10, etc)
    int hitDie;
    array<int, 6> statPriority;
};
/*
 Things a PC will have but not an NPC
 Equipment (choose a, b, or c for 3ish items)
 Background (contains several things)
 Proficiencies (what armor, weapons, and tools youre able to use)
 Skills (choose two from a list based on class)
 Saving throw proficiencies (2 skills)
 Class Features (more unlock as you gain levels)
 Subclass Name
 Subclass Features (more unlock as you gain levels)
 Weapon(s) Name and quantity
 Spell Names (and desciptions)
 Weapon to hit
 Weapon damage
 Starting Wealth
 */

extern map<int, Class> availableClasses;
extern int nextClassID;

void generateBaseClasses();
int saveClasses();
int saveClass(Class toSave);
int sqlToClass(void* data, int argc, char** argv, char** azColName);
int readClasses();
void removeClass(int toRemove);
void removeAllClasses();
void displayClass(Class toDisplay);

static const int cCreateErr = 1116;
static const int cDbErr = 1201;
static const int claIdMismatch = 1210;
static const int claOpenErr = 1211;
static const int claFailRead = 1212;
static const int claFailPrep = 1213;
static const int claFailBind = 1214;

#endif /* Class_hpp */
