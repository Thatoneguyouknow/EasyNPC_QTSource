//
//  Weapon.cpp
//  Dnd
//
//  Created by Benjamin Peterson on 1/22/21.
//

#include "Weapon.hpp"
int nextWeaponID = 0;
map<int, Weapon> availableWeapons;

void generateBaseWeapons()
{
    // generate club
    wProperties prop = wProperties();
    prop.addProperties(vector<int> {LIGHT});
    Weapon Club = Weapon("Club", 4, BLUD, SIMPLE, isMelee, prop);
    availableWeapons.insert(pair<int, Weapon>(Club.getWeaponID(), Club));
    
    // generate dagger
    wProperties prop2 = wProperties();
    prop2.addProperties(vector<int> {FIN, LIGHT, THROW});
    Weapon Dagger = Weapon("Dagger", 4, PEIRCE, SIMPLE, isMelee, prop2);
    availableWeapons.insert(pair<int, Weapon>(Dagger.getWeaponID(), Dagger));
    
    // generate GreatClub
    wProperties prop3 = wProperties();
    prop3.addProperties(vector<int> {TWOH});
    Weapon GreatClub = Weapon("Greatclub", 8, BLUD, SIMPLE, isMelee, prop3);
    availableWeapons.insert(pair<int, Weapon>(GreatClub.getWeaponID(), GreatClub));
    // For user entered weapons, weight is not necessary.
    
}

int propertiesToInt(Weapon w)
{
    int total = 0;
    int value;
    for (int i = 0; i < w.getsetProperties().getProperties().size(); i++)
    {
        value = w.getsetProperties().getProperties()[i] % NONE;
        // this method will not work for value 111, VERS
        // 11 * 10^i is one 0 more than 10 * 10^i-1, it needs to be 2.
        // Howver 10 * 10^i is 2 0s more than 9 * 10^i-1
        // perhaps just an added extra 0 for 111, but that requires that 111 is at the end of the list
        // this problem could be solved by sorting the properties list beforehand?
        // Or a better mathmatical equation to hold the properties list as a single value.
        // Realistically the value shouldn't be over 1 million, but I need something just in case
        if( value == VERS )
        {
            total += (value % 100) * pow(10, i+1);
        }
        else
        {
            total += (value % 100) * pow(10, i);
        }
    }
    //string toPrint = w.getsetName();
    //cout << "Weapon(" << toPrint << ") Properties saved: " << total << "\n";
    return total;
}

void displayWeapon(Weapon w)
{
    cout << "Weapon: \n";
    cout << "ID: " << w.getWeaponID() << "\n";
    cout << "Name: " << w.getsetName() << "\n";
    cout << "Damage: " << w.getsetDmg() << "\n";
    cout << "Damage Type: " << w.getsetDmgType() << "\n";
    cout << "Category: " << w.getsetCategory() << "\n";
    cout << "Melee: " << w.getSetMelee() << "\n";
}


////////////////
// Weapon Class Methods
////////////////
Weapon::Weapon()
{
    WeaponID = nextWeaponID;
    nextWeaponID++;
}

Weapon::Weapon(string wName, int wDamage, int wDType, int wCategory, bool wMelee, wProperties propObject)
{
    WeaponID = nextWeaponID;
    nextWeaponID++;
    name = wName;
    damage = wDamage;
    damageType = wDType;
    category = wCategory;
    melee = wMelee;
    properties = propObject;
}

Weapon::Weapon(const Weapon &toCopy)
{
    WeaponID = toCopy.WeaponID;
    name = toCopy.name;
    damage = toCopy.damage;
    damageType = toCopy.damageType;
    category = toCopy.category;
    melee = toCopy.melee;
    properties = toCopy.properties;
}

Weapon::~Weapon()
{
    
}

int Weapon::getWeaponID()
{
    return WeaponID;
}

string Weapon::getsetName(bool setFlag, string toSet)
{
    if( setFlag )
    {
        name = toSet;
    }
    return name;
}

int Weapon::getsetDmg(bool setFlag, int toSet)
{
    if( setFlag )
    {
        damage = toSet;
    }
    return damage;
}

int Weapon::getsetDmgType(bool setFlag, int toSet)
{
    if( setFlag )
    {
        damageType = toSet;
    }
    return damageType;
}

int Weapon::getsetCategory(bool setFlag, int toSet)
{
    if( setFlag )
    {
        category = toSet;
    }
    return category;
}

bool Weapon::getSetMelee(bool setFlag, bool toSet)
{
    if( setFlag )
    {
        melee = toSet;
    }
    return melee;
}

wProperties Weapon::getsetProperties(bool setFlag, wProperties* toSet)
{
    if( setFlag )
    {
        properties = wProperties(*toSet);
    }
    return properties;
}


////////////////
// Weapon Properties Methods
////////////////
wProperties::wProperties()
{
    Special = "Placeholder";
}

wProperties::wProperties(const wProperties &toCopy)
{
    propertyList = toCopy.propertyList;
    ammoAmmount = toCopy.ammoAmmount;
    range = toCopy.range;
    Special = toCopy.Special;
}

wProperties::~wProperties()
{
    
}

void wProperties::addProperties(vector<int> toAdd, int ammo, int rng, string description)
{
    for(int i=0; i < toAdd.size(); i++)
    {
        propertyList.push_back(toAdd[i]);
    }
    
    ammoAmmount = ammo;
    range = rng;
    Special = description;
}

int wProperties::getsetAmmo(bool setFlag, int toSet)
{
    if( setFlag )
    {
        ammoAmmount = toSet;
    }
    return ammoAmmount;
}

int wProperties::getsetRange(bool setFlag, int toSet)
{
    if( setFlag )
    {
        range = toSet;
    }
    return range;
}

string wProperties::getsetSpecial(bool setFlag, string toSet)
{
    if( setFlag )
    {
        Special = toSet;
    }
    return Special;
}

vector<int> wProperties::getProperties()
{
    return propertyList;
}


////////////////////
// Database Access
///////////////////

void saveWeapons()
{
    for (int counter = 0; counter < availableWeapons.size(); counter++)
    {
        Weapon toSave = availableWeapons[counter];
        saveWeapon(toSave);
    }
}

void saveWeapon(Weapon toSave)
{
    sqlite3* db;
    int success = sqlite3_open("data.db", &db);
    if( success )
    {
        printf("Cannot open database %s\n", sqlite3_errmsg(db));
    }
    
    int returnCode;
    
    const char* sql = "INSERT OR IGNORE INTO WEAPON (ID, NAME, DAMAGE, DMGTYPE, CATEGORY, ISMELEE, PROPERTIES, AMMO, RANGE, SPECIAL) " \
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?); ";
    
    sqlite3_stmt* insert_stmt = NULL;
    returnCode = sqlite3_prepare_v2(db, sql, -1, &insert_stmt, NULL);
    if( returnCode != SQLITE_OK )
    {
        printf("Failed to prepare insert statement %s (%i): %s\n", sql, returnCode, sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    
    // Bind values (1 to indexed)
    returnCode = sqlite3_bind_int(insert_stmt, 1, toSave.getWeaponID());
    if( returnCode != SQLITE_OK )
    {
        printf("Failed bind %d, (%i): \n", 1, returnCode);
    }
    
    string cName = toSave.getsetName();
    char* name = &cName[0];
    returnCode = sqlite3_bind_text(insert_stmt, 2, name, sizeof(toSave.getsetName()), NULL);
    if( returnCode != SQLITE_OK )
    {
        printf("Failed bind %d, (%i): \n", 2, returnCode);
    }
    
    returnCode = sqlite3_bind_int(insert_stmt, 3, toSave.getsetDmg());
    if( returnCode != SQLITE_OK )
    {
        printf("Failed bind %d, (%i): \n", 3, returnCode);
    }
    
    returnCode = sqlite3_bind_int(insert_stmt, 4, toSave.getsetDmgType());
    if( returnCode != SQLITE_OK )
    {
        printf("Failed bind %d, (%i): \n", 4, returnCode);
    }
    
    returnCode = sqlite3_bind_int(insert_stmt, 5, toSave.getsetCategory());
    if( returnCode != SQLITE_OK )
    {
        printf("Failed bind %d, (%i): \n", 5, returnCode);
    }
    
    int isMelee = int(toSave.getSetMelee());
    returnCode = sqlite3_bind_int(insert_stmt, 6, isMelee);
    if( returnCode != SQLITE_OK )
    {
        printf("Failed bind %d, (%i): \n", 6, returnCode);
    }
    
    returnCode = sqlite3_bind_int(insert_stmt, 7, propertiesToInt(toSave));
    if( returnCode != SQLITE_OK )
    {
        printf("Failed bind %d, (%i): \n", 7, returnCode);
    }
    
    returnCode = sqlite3_bind_int(insert_stmt, 8, toSave.getsetProperties().getsetAmmo());
    if( returnCode != SQLITE_OK )
    {
        printf("Failed bind %d, (%i): \n", 8, returnCode);
    }
    
    returnCode = sqlite3_bind_int(insert_stmt, 9, toSave.getsetProperties().getsetRange());
    if( returnCode != SQLITE_OK )
    {
        printf("Failed bind %d, (%i): \n", 9, returnCode);
    }
    
    cName = toSave.getsetProperties().getsetSpecial();
    name = &cName[0];
    returnCode = sqlite3_bind_text(insert_stmt, 10, name, sizeof(toSave.getsetProperties().getsetSpecial()), NULL);
    if( returnCode != SQLITE_OK )
    {
        printf("Failed bind %d, (%i): \n", 10, returnCode);
    }
    
    returnCode = sqlite3_step(insert_stmt);
    if( returnCode != SQLITE_DONE )
    {
        printf("Weapon insert not DONE (%i): %s\n", returnCode, sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(insert_stmt);
        
    sqlite3_close(db);
}

int sqlToWeapon(void* data, int argc, char** argv, char** azColName)
{
    for(int i = 0; i<argc; i++){
       printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    
    int read[8];
    // ID is in read[0]
    sscanf(argv[0], "%d", &read[0]);
    
    string name = argv[1];
    //string special = argv[10];
    
    for( int i=2; i<9; i++)
    {
        sscanf(argv[i], "%d", &read[i-1]);
    }
    
    // read 5-7 are weapon property values
    wProperties newProps = wProperties();
    int propertiesInt = read[5];
    int temp;
    while( propertiesInt != 0 )
    {
        if( propertiesInt % 10 == 0 || propertiesInt % 11 == 0 )
        {
            temp = propertiesInt % 100;
            propertiesInt = propertiesInt - temp;
            propertiesInt = propertiesInt / 100;
        }
        else
        {
            temp = propertiesInt % 10;
            propertiesInt = propertiesInt - temp;
            propertiesInt = propertiesInt / 10;
        }
        temp += 100;
        newProps.addProperties(vector<int> {temp});
    }
    
    newProps.getsetAmmo(true, read[6]);
    newProps.getsetRange(true, read[7]);
    //newProps.getsetSpecial(true, special);
    
    Weapon newWeap = Weapon(name, read[1], read[2], read[3],(bool)read[4], newProps);
    
    if( newWeap.getWeaponID() != read[0] )
    {
        printf("WeaponID does not match SQL Weapon ID");
        // Add return code here
    }
    
    availableWeapons.insert(pair<int, Weapon>(newWeap.getWeaponID(), newWeap));
    
    return 0;
}

void readWeapons()
{
    sqlite3 *db;
    int success = sqlite3_open("data.db", &db);
    if( success )
    {
        printf("Cannot open database %s\n", sqlite3_errmsg(db));
    }
    
    int returnCode;
    char *zErrMsg;
    
    const char* select = "SELECT * from WEAPON";
    returnCode = sqlite3_exec(db, select, sqlToWeapon, 0, &zErrMsg);
    
    if( returnCode != SQLITE_OK )
    {
        printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
        
    sqlite3_close(db);
}
