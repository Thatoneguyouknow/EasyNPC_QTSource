#include "race.h"

int nextRaceID = 0;
int nexSubID = 0;
map<int, Race> availableRaces;

// A function to generate all races in the base Dnd5e set. Will be called upon first start of application.
void generateBaseRaces()
{
    // Instead of doing subraces the way I have been, I'm going to change it
    // TODO: Make each subrace into their own race, add likelihood of seeing some races, Drow unlikely
    Race hDwarf = Race("Hill Dwarf", CONSTITUTION, WISDOM, 2, 1, 350, 50);
    availableRaces.insert(pair<int, Race>(hDwarf.getIdentifier(), hDwarf));

    Race mDwarf = Race("Mountain Dwarf", CONSTITUTION, STRENGTH, 2, 2, 350, 50, hDwarf.getIdentifier());
    availableRaces.insert(pair<int, Race>(mDwarf.getIdentifier(), mDwarf));

    // generate elf
    Race hElf = Race("High Elf", DEXTERITY, INTELLIGENCE, 2, 1, 750, 100);
    availableRaces.insert(pair<int, Race>(hElf.getIdentifier(), hElf));

    Race wElf = Race("Wood Elf", DEXTERITY, WISDOM, 2, 1, 750, 100, hElf.getIdentifier());
    availableRaces.insert(pair<int, Race>(wElf.getIdentifier(), wElf));
    // Dark elf is below with other uncommon races

    // generate halfling
    Race lHalf = Race("Lightfoot Halfling", DEXTERITY, CHARISMA, 2, 1, 250, 20);
    availableRaces.insert(pair<int, Race>(lHalf.getIdentifier(), lHalf));

    Race sHalf = Race("Stout Halfling", DEXTERITY, CONSTITUTION, 2, 1, 250, 20, lHalf.getIdentifier());
    availableRaces.insert(pair<int, Race>(sHalf.getIdentifier(), sHalf));

    // generate human
    // TODO: Figure out human specfic traits
    int hAsi1 = (rand() % 6) + 1;
    int hAsi2 = (rand() % 6) + 1;
    Race human = Race("Human", hAsi1, hAsi2, 1, 1, 95, 18);
    availableRaces.insert(pair<int, Race>(human.getIdentifier(), human));

    // generate dragonborn
    Race dragonborn = Race("Dragonborn", STRENGTH, CHARISMA, 2, 1, 80, 15);
    availableRaces.insert(pair<int, Race>(dragonborn.getIdentifier(), dragonborn));

    // generate gnome
    Race fGnome = Race("Forest Gnome", INTELLIGENCE, DEXTERITY, 2, 1, 500, 40);
    availableRaces.insert(pair<int, Race>(fGnome.getIdentifier(), fGnome));

    Race rGnome = Race("Rock Gnome", INTELLIGENCE, CONSTITUTION, 2, 1, 500, 40, fGnome.getIdentifier());
    availableRaces.insert(pair<int, Race>(rGnome.getIdentifier(), rGnome));

    // generate half-elf
    // TODO: Add Constructor for race with 3 asi
    Race half_elf = Race("Half-Elf", CHARISMA, CHARISMA, 2, 2, 220, 20);
    availableRaces.insert(pair<int, Race>(half_elf.getIdentifier(), half_elf));

    // generate half-orc
    Race halfOrc = Race("Half-Orc", STRENGTH, CONSTITUTION, 2, 1, 75, 14);
    availableRaces.insert(pair<int, Race>(halfOrc.getIdentifier(), halfOrc));

    // generate tiefling
    Race tiefling = Race("Tiefling", INTELLIGENCE, CHARISMA, 1, 2, 150, 20);
    availableRaces.insert(pair<int, Race>(tiefling.getIdentifier(), tiefling));

    Race dElf = Race("Dark Elf", DEXTERITY, CHARISMA, 2, 1, 750, 100, hElf.getIdentifier());
    availableRaces.insert(pair<int, Race>(dElf.getIdentifier(), dElf));
}

Race::Race()
{

}

Race::Race(string name, int asiStatPrim, int asiStatSec, int asiValPrim, int asiValSec, int maxAge, int minAge, int type)
{
    raceIdentifier = nextRaceID;
    nextRaceID++;
    raceName = name;
    asiStatPrimary = asiStatPrim;
    asiStatSecondary = asiStatSec;
    asiValPrimary = asiValPrim;
    asiValSecondary = asiValSec;
    ageMax = maxAge;
    ageMin = minAge;
    if(type == NOTYPE)
    {
        nameType = raceIdentifier;
    }
    else
    {
        nameType = type;
    }
}

Race::~Race()
{

}

//////////////////////
// Getters and Setters
//////////////////////
string Race::getsetName(bool setFlag, string toSet)
{
    if(setFlag)
    {
        raceName=toSet;
    }
    return raceName;
}

int Race::getsetPrimStat(bool setFlag, int toSet)
{
    if(setFlag)
    {
        asiStatPrimary=toSet;
    }
    return asiStatPrimary;
}

int Race::getsetSecStat(bool setFlag, int toSet)
{
    if(setFlag)
    {
        asiStatSecondary=toSet;
    }
    return asiStatSecondary;
}

int Race::getsetPrimVal(bool setFlag, int toSet)
{
    if(setFlag)
    {
        asiValPrimary=toSet;
    }
    return asiValPrimary;
}

int Race::getsetSecVal(bool setFlag, int toSet)
{
    if(setFlag)
    {
        asiValSecondary=toSet;
    }
    return asiValSecondary;
}

int Race::getsetMaxAge(bool setFlag, int toSet)
{
    if(setFlag)
    {
        ageMax=toSet;
    }
    return ageMax;
}

int Race::getsetMinAge(bool setFlag, int toSet)
{
    if(setFlag)
    {
        ageMin=toSet;
    }
    return ageMin;
}

int Race::getsetNameType(bool setFlag, int toSet)
{
    if(setFlag)
    {
        nameType=toSet;
    }
    return nameType;
}

int Race::getIdentifier()
{
    return raceIdentifier;
}



/////////////////
// SQL Functions
/////////////////
int sqlToRace(void *data, int argc, char **argv, char **azColName)
{
    int read[7];
    int ID;
    Race newRace;

    string name = argv[1];
    sscanf(argv[0], "%d", &ID);

    for( int i=2; i<argc; i++)
    {
        sscanf(argv[i], "%d", &read[i-2]);
    }

    // add try-catch here
    try {
        newRace = Race(name, read[0], read[1], read[2], read[3], read[4], read[5], read[6]);
    }  catch (...) {
        QString error = "Could not generate Race from sql: ";
        error.append(QString::number(ID));
      //  logError(rCreateErr, error, getlogDir());
        return -1;
    }

    if(newRace.getIdentifier() != ID)
    {
        //ErrorCode 1205
        QString error = "RaceID does not match SQL RaceID: ";
        error.append(QString::number(ID));
        logError(raceIdMismatch, error);
        printf("RaceID does not match SQL raceID\n");
    }
    availableRaces.insert(pair<int, Race>(newRace.getIdentifier(), newRace));

    return 0;
}

int readRaces()
{
    sqlite3 *db;

    QDir databaseDir = getlogDir();
    QString database = databaseDir.filePath("data.db");
    QByteArray ba = database.toLocal8Bit();
    const char *data = ba.data();

    int success = sqlite3_open(data, &db);
    if( success )
    {
        QString error = "Cannot open database: ";
        error.append(QString::fromStdString(sqlite3_errmsg(db)));
        logError(raceOpenErr, error);
        //printf("Cannot open database %s\n", sqlite3_errmsg(db));
        return -1;
    }

    int returnCode;
    char *zErrMsg;

    const char* select = "SELECT * from RACE";
    returnCode = sqlite3_exec(db, select, sqlToRace, 0, &zErrMsg);

    if( returnCode != SQLITE_OK )
    {
        QString error = "Race Read Error: ";
        error.append(QString::fromStdString(zErrMsg));
        logError(raceFailRead, error);
        //printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }

    sqlite3_close(db);
    return 0;
}

int saveRaces()
{
    map<int, Race>::iterator it;
    for( it=availableRaces.begin(); it!=availableRaces.end(); it++ )
    {
        Race toSave = it->second;
        if( saveRace(toSave) == -1 )
        {
            return -1;
        }
    }
    return 0;
}

int saveRace(Race toSave)
{
    sqlite3 *db;

    QDir databaseDir = getlogDir();
    QString database = databaseDir.filePath("data.db");
    QByteArray ba = database.toLocal8Bit();
    const char *data = ba.data();

    int success = sqlite3_open(data, &db);
    if( success )
    {
        // ErrorCode 1201
        QString error = "Cannot open database ";
        error.append(sqlite3_errmsg(db));
        logError(rDbErr, error);
        //printf("Cannot open database %s\n", sqlite3_errmsg(db));
        return -1;
    }

    int returnCode;

    const char* sql = "INSERT OR IGNORE INTO RACE (ID, NAME, ASIPSTAT, ASISSTAT, ASIPVAL, ASISVAL, AGEMAX, AGEMIN, NAMETYPE)" \
            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)"\
            "ON CONFLICT(ID) DO UPDATE SET "\
            "NAME=excluded.NAME, ASIPSTAT=excluded.ASIPSTAT, ASISSTAT=excluded.ASISSTAT,"\
            "ASIPVAL=excluded.ASIPVAL, ASISVAL=excluded.ASISVAL, AGEMAX=excluded.AGEMAX, AGEMIN=excluded.AGEMIN, NAMETYPE=excluded.NAMETYPE;";

    // Prepare insert statement
    sqlite3_stmt *insert_stmt = NULL;
    returnCode = sqlite3_prepare_v2(db, sql, -1, &insert_stmt, NULL);
    if(returnCode != SQLITE_OK )
    {
        // ErrorCode 1208
        QString error = "Failed to prepare insert statement INSERT INTO RACE ";
        error.append(QString::number(returnCode));
        error.append(": ");
        error.append(sqlite3_errmsg(db));
        logError(raceFailPrep, error);
        //printf("Failed to prepare insert statement %s (%i): %s\n", sql, returnCode, sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }
    else
    {
        // Bind values (1 to indexed)
        returnCode = sqlite3_bind_int(insert_stmt, 1, toSave.getIdentifier());
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1209
            QString error = "Failed bind ";
            error.append(QString::number(1));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(raceFailBind, error);
            //printf("Failed bind %d, (%i): \n", 1, returnCode);
            return -1;
        }

        string cName = toSave.getsetName();
        char* name = &cName[0];
        returnCode = sqlite3_bind_text(insert_stmt, 2, name, sizeof(toSave.getsetName()), NULL);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1209
            QString error = "Failed bind ";
            error.append(QString::number(2));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(raceFailBind, error);
            //printf("Failed bind %d, (%i): \n", 2, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 3, toSave.getsetPrimStat());
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1209
            QString error = "Failed bind ";
            error.append(QString::number(3));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(raceFailBind, error);
            //printf("Failed bind %d, (%i): \n", 3, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 4, toSave.getsetSecStat());
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1209
            QString error = "Failed bind ";
            error.append(QString::number(4));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(raceFailBind, error);
            //printf("Failed bind %d, (%i): \n", 4, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 5, toSave.getsetPrimVal());
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1209
            QString error = "Failed bind ";
            error.append(QString::number(5));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(raceFailBind, error);
            //printf("Failed bind %d, (%i): \n", 5, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 6, toSave.getsetSecVal());
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1209
            QString error = "Failed bind ";
            error.append(QString::number(6));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(raceFailBind, error);
            //printf("Failed bind %d, (%i): \n", 6, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 7, toSave.getsetMaxAge());
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1209
            QString error = "Failed bind ";
            error.append(QString::number(7));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(raceFailBind, error);
            //printf("Failed bind %d, (%i): \n", 7, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 8, toSave.getsetMinAge());
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1209
            QString error = "Failed bind ";
            error.append(QString::number(8));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(raceFailBind, error);
            //printf("Failed bind %d, (%i): \n", 8, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 9, toSave.getsetNameType());
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1209
            QString error = "Failed bind ";
            error.append(QString::number(9));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(raceFailBind, error);
            //printf("Failed bind %d, (%i): \n", 9, returnCode);
            return -1;
        }

        returnCode = sqlite3_step(insert_stmt);
        if (returnCode != SQLITE_DONE)
        {
            // ErrorCode 1209
            QString error = "Insert stmt did not return DONE ";
            error.append(QString::number(returnCode));
            error.append(": ");
            error.append(QString::fromStdString(sqlite3_errmsg(db)));
            logError(raceFailBind, error);
            //printf("Insert statement did not return DONE (%i): %s\n", returnCode, sqlite3_errmsg(db));
            return -1;
        }

        sqlite3_finalize(insert_stmt);

        sqlite3_close(db);
        return 0;
    }
}

void removeRace(int toRemove)
{
    int returnCode;
    const char* del = "DELETE FROM RACE "\
                        "WHERE ID = ?";
    sqlite3_stmt* insert_stmt = NULL;

    sqlite3* db;

    QDir databaseDir = getlogDir();
    QString database = databaseDir.filePath("data.db");
    QByteArray ba = database.toLocal8Bit();
    const char *data = ba.data();

    int success = sqlite3_open(data, &db);
    if( success )
    {
        // ErrorCode 1206
        printf("Cannot open database%s\n", sqlite3_errmsg(db));
    }

    returnCode = sqlite3_prepare_v2(db, del, -1, &insert_stmt, NULL);
    if(returnCode != SQLITE_OK)
    {
        // ErrorCode 1208
        printf("Failed to prepare delete statement %s (%i): %s\n", del, returnCode, sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    returnCode = sqlite3_bind_int(insert_stmt, 1, toRemove);
    if (returnCode != SQLITE_DONE)
    {
        // ErrorCode 1209
        printf("Failed Bind %d (%i): \n", 1, returnCode);
    }

    sqlite3_finalize(insert_stmt);
    sqlite3_close(db);
}

void removeAllRaces()
{
    int returnCode;
    const char* del = "DELETE FROM RACE "\
                        "WHERE ID = ?";
    sqlite3_stmt* insert_stmt = NULL;

    map<int, Race>::iterator it;
    for( it = availableRaces.begin(); it != availableRaces.end(); it++ )
    {
        sqlite3* db;

        QDir databaseDir = getlogDir();
        QString database = databaseDir.filePath("data.db");
        QByteArray ba = database.toLocal8Bit();
        const char *data = ba.data();

        int success = sqlite3_open(data, &db);
        if( success )
        {
            // ErrorCode 1206
            printf("Cannot open database%s\n", sqlite3_errmsg(db));
        }

        returnCode = sqlite3_prepare_v2(db, del, -1, &insert_stmt, NULL);
        if(returnCode != SQLITE_OK)
        {
            // ErrorCode 1208
            printf("Failed to prepare delete statement %s (%i): %s\n", del, returnCode, sqlite3_errmsg(db));
            sqlite3_close(db);
        }

        returnCode = sqlite3_bind_int(insert_stmt, 1, it->first);
        if (returnCode != SQLITE_DONE)
        {
            // ErrorCode 1209
            printf("Failed Bind %d (%i): \n", 1, returnCode);
        }

        sqlite3_finalize(insert_stmt);
        sqlite3_close(db);
    }
}
