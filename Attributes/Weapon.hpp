//
//  Weapon.hpp
//  Dnd
//
//  Created by Benjamin Peterson on 1/22/21.
//

#ifndef Weapon_hpp
#define Weapon_hpp

#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <sqlite3.h>
#include "Stats.hpp"
#include <vector>

using namespace std;

enum properties {AMMO=101, FIN, HEAVY, LIGHT, LOAD, RANGE, REACH, SPEC, THROW, TWOH, VERS, NONE};
enum dmgTypes {BLUD=10, PEIRCE, SLASH};
enum categories {SIMPLE=20, MARTI};
const bool isMelee = false;
const bool isRanged = true;

class wProperties
{
public:
    wProperties();
    wProperties(const wProperties &toCopy);
    ~wProperties();
    wProperties& operator=(const wProperties& other)
    {
        if( this != &other )
        {
            propertyList = other.propertyList;
            ammoAmmount = other.ammoAmmount;
            range = other.range;
            Special = other.Special;
        }
        return *this;
    }

    void addProperties(vector<int> toAdd, int ammo=0, int rng=0, string description="");
    int getsetAmmo(bool setFlag=false, int toSet=0);
    int getsetRange(bool setFlag=false, int toSet=0);
    vector<int> getProperties();
    string getsetSpecial(bool setFlag=false, string toSet="");
    
private:
    int ammoAmmount;
    int range;
    string Special;
    vector<int> propertyList;
};
// Weapon Properties: This should be it's own object pointed to by the Weapon Object
    // Ammo, for ranged weapon; Improvised weapon if used for a melee attack
    // Finesse, Choose STR or DEX for both rolls
    // Heavy, Disadvantage on SMALL creatures
    // Light, good for two-weapon fighting
    // Loading, property of having to load a weapon with ammo
    // Range, the distance you can attack from
    // Reach, added 5ft of range
    // Special, an extra special property
    // Thrown, Can throw weapon for a ranged attack
    // Two-Handed, requires both hands
    // Versatile, Can be used with 1 or 2 hands



class Weapon
{
public:
    Weapon();
    Weapon(string wName, int wDamage, int wDType, int wCategory, bool wMelee, wProperties propObject);
    Weapon(const Weapon &toCopy);
    ~Weapon();
    Weapon& operator=(const Weapon& other)
    {
        if( this != &other )
        {
            WeaponID = other.WeaponID;
            name = other.name;
            damage = other.damage;
            damageType = other.damageType;
            category = other.category;
            melee = other.melee;
            properties = other.properties;
        }
        return *this;
    }
    
    
    int getWeaponID();
    string getsetName(bool setFlag=false, string toSet="");
    int getsetDmg(bool setFlag=false, int toSet=0);
    int getsetDmgType(bool setFlag=false, int toSet=0);
    int getsetCategory(bool setFlag=false, int toSet=0);
    bool getSetMelee(bool setFlag=false, bool toSet=false);
    wProperties getsetProperties(bool setFlag=false, wProperties* toSet=nullptr);
private:
    // Weapons are either melee or ranged
    // Weapons have categories: simple and martial
        // simple weapons can be used by anyone with proficiency (clubs, maces, etc)
        // martial require training for proficiency (swords, axes, polearms, etc)
    int WeaponID;
    string name;
    // damage is the dice to use (d8, d4, etc)
    int damage;
    // damage type (bludgeoning, piercing, slashing)
    int damageType;
    int category;
    bool melee;
    wProperties properties;
    
};

extern map<int, Weapon> availableWeapons;
extern int nextWeaponID;

void generateBaseWeapons();
int propertiesToInt(Weapon w);
void saveWeapons();
void saveWeapon(Weapon toSave);
int sqlToWeapon(void* data, int argc, char** argv, char** azColName);
void readWeapons();

// for testing purposes only
void displayWeapon(Weapon w);

#endif /* Weapon_hpp */
