#include "class.h"

int nextClassID = 0;
map<int, Class> availableClasses;

void generateBaseClasses()
{
    // generate Barbarian
    Class barbarian = Class("Barbarian", 12,  array<int, 6> {STRENGTH, CONSTITUTION, WISDOM, INTELLIGENCE, CHARISMA, DEXTERITY}, 6);
    availableClasses.insert(pair<int, Class>(barbarian.getClassID(), barbarian));

    // generate Bard
    Class bard = Class("Bard", 8, array<int, 6> {CHARISMA, DEXTERITY, CONSTITUTION, WISDOM, INTELLIGENCE, STRENGTH}, 6);
    availableClasses.insert(pair<int, Class>(bard.getClassID(), bard));

    // generate Cleric
    Class cleric = Class("Cleric", 8, array<int, 6> {WISDOM, STRENGTH, CONSTITUTION, INTELLIGENCE, CHARISMA, DEXTERITY}, 6);
    availableClasses.insert(pair<int, Class>(cleric.getClassID(), cleric));

    // generate Druid
    Class druid = Class("Druid", 8, array<int, 6> {WISDOM, CONSTITUTION, INTELLIGENCE, CHARISMA, DEXTERITY, STRENGTH}, 6);
    availableClasses.insert(pair<int, Class>(druid.getClassID(), druid));

    // generate Fighter
    // Different sub-types of fighters will have different stat preferences
    //*Dex for archer/finesse weapon choices
    //**Int for Eldritch Knight subclass
    Class fighter = Class("Fighter", 8, array<int, 6> {STRENGTH, CONSTITUTION, DEXTERITY, WISDOM, INTELLIGENCE, CHARISMA}, 6);
    availableClasses.insert(pair<int, Class>(fighter.getClassID(), fighter));

    // generate Monk
    Class monk = Class("Monk", 8, array<int, 6> {DEXTERITY, WISDOM, CONSTITUTION, CHARISMA, STRENGTH, INTELLIGENCE}, 6);
    availableClasses.insert(pair<int, Class>(monk.getClassID(), monk));

    // generate Paladin
    //*Cha for spell emphasis, can be random
    Class paladin = Class("Paladin", 10, array<int, 6> {STRENGTH, CHARISMA, CONSTITUTION, WISDOM, INTELLIGENCE, DEXTERITY}, 6);
    availableClasses.insert(pair<int, Class>(paladin.getClassID(), paladin));

    // generate Ranger
    Class ranger = Class("Ranger", 10, array<int, 6> {DEXTERITY, WISDOM, CONSTITUTION, INTELLIGENCE, STRENGTH, CHARISMA}, 6);
    availableClasses.insert(pair<int, Class>(ranger.getClassID(), ranger));

    // generate Rogue
        //Subclasses:* Thief (Cha), Assassin (Cha), Arcane Trickster (Int)
    Class rogue = Class("Rogue", 8, array<int, 6> {DEXTERITY, CHARISMA, CONSTITUTION, INTELLIGENCE, WISDOM, STRENGTH}, 6);
    availableClasses.insert(pair<int, Class>(rogue.getClassID(), rogue));

    // generate Sorcerer
    Class sorcerer = Class("Sorcerer", 6, array<int, 6> {CHARISMA, CONSTITUTION, DEXTERITY, INTELLIGENCE, WISDOM, STRENGTH}, 6);
    availableClasses.insert(pair<int, Class>(sorcerer.getClassID(), sorcerer));

    // generate Warlock
    Class warlock = Class("Warlock", 8, array<int, 6> {CHARISMA, CONSTITUTION, WISDOM, INTELLIGENCE, DEXTERITY, STRENGTH}, 6);
    availableClasses.insert(pair<int, Class>(warlock.getClassID(), warlock));

    // generate Wizard
    Class wizard = Class("Wizard", 6, array<int, 6> {INTELLIGENCE, CONSTITUTION, DEXTERITY, WISDOM, CHARISMA, STRENGTH}, 10);
    availableClasses.insert(pair<int, Class>(wizard.getClassID(), wizard));

   /* map<int, Class>::iterator it;
    for( it = availableClasses.begin(); it != availableClasses.end(); it++ )
    {
        cout << it->second.getsetName() << ": " << it->second.getsetUser() << "\n";
    }*/
}

Class::Class()
{

}

Class::Class(string cName, int hitdie, array<int, 6> priority, int userMade)
{
    classID = nextClassID;
    nextClassID++;
    name = cName;
    hitDie = hitdie;
    statPriority = priority;
    userCreated = userMade;
}

Class::~Class()
{

}

string Class::getsetName(bool setFlag, string toSet)
{
    if(setFlag)
    {
        name = toSet;
    }
    return name;
}

int Class::getsetHitDie(bool setFlag, int toSet)
{
    if(setFlag)
    {
        hitDie = toSet;
    }
    return hitDie;
}

array<int, 6> Class::getsetPriority(bool setFlag, array<int, 6>* toSet)
{
    if(setFlag)
    {
        for( int counter=0; counter < 6; counter++)
        {
            statPriority = *toSet;
        }
    }
    return statPriority;
}

int Class::getsetUser(bool setFlag, int toSet)
{
    if(setFlag)
    {
        userCreated = toSet;
    }
    return userCreated;
}


int Class::getClassID()
{
    return classID;
}




//////////////////////
// Database Access
//////////////////////
int sqlToClass(void* data, int argc, char** argv, char** azColName) {
    int read[7];
    string name = argv[1];
    int id;
    sscanf(argv[0], "%d", &id);

    // i+2 is the offset for the first two values in argv being id and name respectively
    for( int i=0; i+2<argc-1; i++)
    {
        sscanf(argv[i+2], "%d", &read[i]);
    }

    Class newClass;
    try {
        newClass = Class(name, read[0], array<int, 6> {read[1], read[2], read[3], read[4], read[5], read[6]}, (bool)argv[argc]);
    }  catch (...) {
        QString error = "Could not generate Class from sql: ";
        error.append(QString::number(id));
        logError(cCreateErr, error);
        return -1;
    }

    if(newClass.getClassID() != id)
    {
        // ErrorCode 1210
        QString error = "ClassID does not match SQL classID: ";
        error.append(QString::number(id));
        logError(claIdMismatch, error);
        //printf("ClassID does not match SQL classID");
        return -1;
    }

    availableClasses.insert(pair<int, Class>(newClass.getClassID(), newClass));
    return 0;
}

int readClasses()
{
    sqlite3 *db;

    QDir databaseDir = getlogDir();
    QString database = databaseDir.filePath("data.db");
    QByteArray ba = database.toLocal8Bit();
    const char *data = ba.data();

    int success = sqlite3_open(data, &db);
    if( success )
    {
        // ErrorCode 1211
        QString error = "Cannot open database: ";
        error.append(QString::fromStdString(sqlite3_errmsg(db)));
        logError(claOpenErr, error);
        //printf("Cannot open database %s\n", sqlite3_errmsg(db));
        return -1;
    }

    int returnCode;
    char *zErrMsg;

    const char* select = "SELECT * from CLASS";
    returnCode = sqlite3_exec(db, select, sqlToClass, 0, &zErrMsg);

    if( returnCode != SQLITE_OK )
    {
        // ErrorCode 1212
        QString error = "Class Read Error: ";
        error.append(QString::fromStdString(zErrMsg));
        logError(claFailRead, error);
        //printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }

    sqlite3_close(db);
    return 0;
}


int saveClasses()
{
    map<int, Class>::iterator it;
    for( it=availableClasses.begin(); it!=availableClasses.end(); it++ )
    {
        Class toSave = it->second;
        if( saveClass(toSave) == -1 )
        {
            // return out of saving
            // throw error
            return -1;
        }
    }
    return 0;
}

int saveClass(Class toSave)
{
    sqlite3* db;

    QDir databaseDir = getlogDir();
    QString database = databaseDir.filePath("data.db");
    QByteArray ba = database.toLocal8Bit();
    const char *data = ba.data();

    int success = sqlite3_open(data, &db);
    if (success)
    {
        // ErrorCode 1201
        QString error = "Cannot open database: ";
        error.append(QString::fromStdString(sqlite3_errmsg(db)));
        logError(cDbErr, error);

        return -1;
    }

    int returnCode;

    const char* sql = "INSERT OR IGNORE INTO CLASS (ID, NAME, HITDIE, P1STAT, P2STAT, P3STAT, P4STAT, P5STAT, P6STAT, USERMADE) " \
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?) "\
        "ON CONFLICT(ID) DO UPDATE SET "\
        "NAME=excluded.NAME, HITDIE=excluded.HITDIE, P1STAT=excluded.P1STAT, "\
        "P2STAT=excluded.P2STAT, P3STAT=excluded.P3STAT, P4STAT=excluded.P4STAT, P5STAT=excluded.P5STAT, P6STAT=excluded.P6STAT, USERMADE=excluded.USERMADE;";

    // Prepare insert statmenet
    sqlite3_stmt* insert_stmt = NULL;
    returnCode = sqlite3_prepare_v2(db, sql, -1, &insert_stmt, NULL);
    if (returnCode != SQLITE_OK)
    {
        // ErrorCode 1213
        QString error = "Failed to prepare insert statement 'INSERT INTO CLASS' (";
        error.append(QString::number(returnCode));
        error.append("): ");
        error.append(QString::fromStdString(sqlite3_errmsg(db)));
        logError(claFailPrep, error);
        //printf("Failed to prepare insert statement %s (%i): %s\n", sql, returnCode, sqlite3_errmsg(db));
        sqlite3_close(db);

        return -1;
    }
    else
    {
        // Bind values (1 to indexed)
        returnCode = sqlite3_bind_int(insert_stmt, 1, toSave.getClassID());
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1214
            QString error = "Failed bind ";
            error.append(QString::number(1));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(claFailBind, error);
            //printf("Failed bind %d, (%i): \n", 1, returnCode);
            return -1;
        }

        string cName = toSave.getsetName();
        char* name = &cName[0];
        returnCode = sqlite3_bind_text(insert_stmt, 2, name, sizeof(toSave.getsetName()), NULL);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1214
            QString error = "Failed bind ";
            error.append(QString::number(2));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(claFailBind, error);
            //printf("Failed bind %d, (%i): \n", 2, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 3, toSave.getsetHitDie());
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1214
            QString error = "Failed bind ";
            error.append(QString::number(3));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(claFailBind, error);
            //printf("Failed bind %d, (%i): \n", 3, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 4, toSave.getsetPriority()[0]);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1214
            QString error = "Failed bind ";
            error.append(QString::number(4));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(claFailBind, error);
            //printf("Failed bind %d, (%i): \n", 4, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 5, toSave.getsetPriority()[1]);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1214
            QString error = "Failed bind ";
            error.append(QString::number(5));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(claFailBind, error);
            //printf("Failed bind %d, (%i): \n", 5, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 6, toSave.getsetPriority()[2]);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1214
            QString error = "Failed bind ";
            error.append(QString::number(6));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(claFailBind, error);
            //printf("Failed bind %d, (%i): \n", 6, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 7, toSave.getsetPriority()[3]);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1214
            QString error = "Failed bind ";
            error.append(QString::number(7));
            error.append(", ");
            error.append(QString::number(returnCode));
           logError(claFailBind, error);
            //printf("Failed bind %d, (%i): \n", 7, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 8, toSave.getsetPriority()[4]);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1214
            QString error = "Failed bind ";
            error.append(QString::number(8));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(claFailBind, error);
            //printf("Failed bind %d, (%i): \n", 8, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 9, toSave.getsetPriority()[5]);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1214
            QString error = "Failed bind ";
            error.append(QString::number(9));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(claFailBind, error);
            //printf("Failed bind %d, (%i): \n", 9, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 10, (int)toSave.getsetUser());
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1214
            QString error = "Failed bind ";
            error.append(QString::number(10));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(claFailBind, error);
            //printf("Failed bind %d, (%i): \n", 10, returnCode);
            return -1;
        }

        returnCode = sqlite3_step(insert_stmt);
        if (returnCode != SQLITE_DONE)
        {
            // ErrorCode 1214
            QString error = "Insert stmt did not return DONE ";
            error.append(QString::number(returnCode));
            error.append(": ");
            error.append(QString::fromStdString(sqlite3_errmsg(db)));
            logError(claFailBind, error);
            //printf("Insert statement did not return DONE (%i): %s\n", returnCode, sqlite3_errmsg(db));
            return -1;
        }
    }

    sqlite3_finalize(insert_stmt);

    sqlite3_close(db);
    return 0;
}

void removeClass(int toRemove)
{
    int returnCode;
    const char* del = "DELETE FROM CLASS "\
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
        // ErrorCode 1211
        printf("Cannot open database%s\n", sqlite3_errmsg(db));
    }

    returnCode = sqlite3_prepare_v2(db, del, -1, &insert_stmt, NULL);
    if(returnCode != SQLITE_OK)
    {
        // ErrorCode 1213
        printf("Failed to prepare delete statement %s (%i): %s\n", del, returnCode, sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    returnCode = sqlite3_bind_int(insert_stmt, 1, toRemove);
    if (returnCode != SQLITE_DONE)
    {
        // ErrorCode 1214
        printf("Delete statement did not return DONE (%i): %s\n", returnCode, sqlite3_errmsg(db));
    }

    sqlite3_finalize(insert_stmt);
    sqlite3_close(db);
}

void removeAllClasses()
{
    int returnCode;
    const char* del = "DELETE FROM CLASS "\
                        "WHERE ID = ?";
    sqlite3_stmt* insert_stmt = NULL;

    map<int, Class>::iterator it;
    for( it = availableClasses.begin(); it != availableClasses.end(); it++ )
    {
        sqlite3* db;

        QDir databaseDir = getlogDir();
        QString database = databaseDir.filePath("data.db");
        QByteArray ba = database.toLocal8Bit();
        const char *data = ba.data();

        int success = sqlite3_open(data, &db);
        if( success )
        {
            // ErrorCode 1211
            printf("Cannot open database%s\n", sqlite3_errmsg(db));
        }

        returnCode = sqlite3_prepare_v2(db, del, -1, &insert_stmt, NULL);
        if(returnCode != SQLITE_OK)
        {
            // ErrorCode 1213
            printf("Failed to prepare delete statement %s (%i): %s\n", del, returnCode, sqlite3_errmsg(db));
            sqlite3_close(db);
        }

        returnCode = sqlite3_bind_int(insert_stmt, 1, it->first);
        if (returnCode != SQLITE_DONE)
        {
            // ErrorCode 1214
            printf("Delete statement did not return DONE (%i): %s\n", returnCode, sqlite3_errmsg(db));
        }

        sqlite3_finalize(insert_stmt);
        sqlite3_close(db);
    }
}
