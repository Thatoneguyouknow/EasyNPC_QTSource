#include "generator.h"

map<int, Generator>availableGens;
int nextGenID = 0;

Generator::Generator(bool empty)
{
    ID = generateId();
    if( !empty )
    {
        race = generateRace();
        name = generateName();
        charClass = generateClass();
        alignment = generateAlign();

        level = generateLevel();
        // TODO: Have level generated and stats, feats, etc changed accurately

        stats = generateStats(charClass);
        hp = calculateHP(charClass);
        personality = generatePersonailty();
    }
}

Generator::Generator(int id)
{
    ID = id;
}

void displayGenerator(Generator display)
{
    cout << "Name: " << display.getsetName() << "\n";
    cout << "Race: " << availableRaces[display.getsetRace()].getsetName() << "\n";
    cout << "Class: " << availableClasses[display.getsetClass()].getsetName() << "\n";
    cout << "Alignment: " << belief.at(display.getsetAlign()[0]) << moral.at(display.getsetAlign()[1]) << "\n";
    cout << "Level: " << display.getsetLevel() << "\n";
    cout << "Stats:\n";
    cout << "  Strength: " << display.getsetStats()[0] << "\n";
    cout << "  Dexterity: " << display.getsetStats()[1] << "\n";
    cout << "  Constitution: " << display.getsetStats()[2] << "\n";
    cout << "  Intelligence: " << display.getsetStats()[3] << "\n";
    cout << "  Wisdom: " << display.getsetStats()[4] << "\n";
    cout << "  Charisma: " << display.getsetStats()[5] << "\n";
    cout << "HP: " << display.getsetHP() << "\n";
    cout << "Personality: " << display.getsetPerson().toStdString() << "\n";
}

int rollStat()
{
    // mean roll of 4 dice should be 14
    // std dev of 4 rolls should be 3
    // reference https://mathworld.wolfram.com/Dice.html
    // roll a normal distribution of 4 dice, subtract a regular random roll of 1 dice
    // We may skew the data and values in the player's favor by putting mean roll at 16
    // https://www.cplusplus.com/reference/random/normal_distribution/
    // sum of all stats should be around 78. I can use that full sum to modify values if they are too low
    int roll1 = (rand() % 6) + 1;
    int roll2 = (rand() % 6) + 1;
    int roll3 = (rand() % 6) + 1;
    int roll4 = (rand() % 6) + 1;
    int sum;
    if( roll1 <= roll2 && roll1 <= roll3 && roll1 <= roll4)
    {
        sum = roll2 + roll3 + roll4;
    }
    else if (roll2 <= roll1 && roll2 <= roll3 && roll2 <= roll4)
    {
        sum = roll1 + roll3 + roll4;
    }
    else if (roll3 <= roll1 && roll3 <= roll2 && roll3 <= roll4)
    {
        sum = roll1 + roll2 + roll4;
    }
    else
    {
        sum = roll1 + roll2 + roll3;
    }

    if( sum < 8 )
    {
        sum = 8;
    }

    return sum;
}


///////////////////////
// Generation Functions
///////////////////////
int Generator::generateId()
{
    // generate an id
    int GenId = rand();

    // check that id isn't equal to another generator's id
    GenId = checkId(GenId);

    return GenId;
}

string Generator::generateName()
{
    string name = createName(availableRaces[race].getsetNameType());
    if( name.compare("Error") == 0 )
    {
        // emit error
        //
        // Set Default: "Jeff"
        name = "Jeff";
    }
    return name;
}

int Generator::generateRace()
{
    return  rand() % availableRaces.size();
}

int Generator::generateClass()
{
    return rand() % availableClasses.size();
}

array<int, 2> Generator::generateAlign()
{
    int bel = abs((int)rand() % 3);
    int mor = abs((int)rand() % 3);
    return array<int, 2> {bel, mor};
}

int Generator::generateLevel()
{
    // for now we will only make level 1 characters
    int cLevel = rand() % 20;
    cLevel += 1;
    return 1;
}

array<int, 6> Generator::generateStats(int cClass)
{
    array<int, 6> rolls;
    rolls = {rollStat(), rollStat(), rollStat(), rollStat(), rollStat(), rollStat()};
    int priority;

    // sort rolls
    bool switchFlag = true;
    int temp;
    while(switchFlag)
    {
        switchFlag = false;
        for(int count = 1; count<(int)rolls.size(); count++)
        {
            if(rolls[count-1] < rolls[count])
            {
                temp = rolls[count];
                rolls[count] = rolls[count-1];
                rolls[count-1] = temp;
                switchFlag = true;
            }
        }
    }

    // set stats up in correct priority
    for(int counter=0; counter<6; counter++)
    {
        priority = availableClasses[cClass].getsetPriority()[counter];
        stats[priority] = rolls[counter];
    }

    //TODO: add in ASI's
        // add if clause for half-elf
    stats[availableRaces[race].getsetPrimStat()] += availableRaces[race].getsetPrimVal();
    stats[availableRaces[race].getsetSecStat()] += availableRaces[race].getsetSecVal();

    return stats;
}

int Generator::calculateHP(int cClass)
{
    // based on class
    int baseHP = availableClasses[cClass].getsetHitDie();
    // calculate constitution modifier, not base constitution value
    int constitution = calcModifier(stats[CONSTITUTION]);
    return baseHP + constitution;
}

QString Generator::generatePersonailty()
{
    // select randomly from a personality bank
    // Assign 1 trait from each of the categories (+, neutral, -)
    // String format should be "P trait, N trait, Ne trait"
    QString personalityTraits;

    // Get Positive Trait
    QString posFileName(":/TextFiles/Positive.txt");
    int numLines = getNumLines(posFileName);
    if( numLines == -1 )
    {
        // Emit Error to MainWindow
        //emit errorCaught(lineNumErr);
        // set Default, 1
        numLines = 1;
    }
    int traitNum = rand() % numLines + 1;
    QString trait = getLineAt(posFileName, traitNum);
    if( trait.compare("Error") == 0 )
    {
        // Emit Error to MainWindow
        //emit errorCaught(lineReadErr);
        // setDefault, "Neat"
        trait = "Neat";
    }
    personalityTraits.append(trait);

    // Get Neutral Trait
    QString neuFileName(":/TextFiles/Neutral.txt");
    numLines = getNumLines(neuFileName);
    if( numLines == -1 )
    {
        // Emit Error to MainWindow
        //emit errorCaught(lineNumErr);
        // setDefault, 1
        numLines = 1;
    }
    traitNum = rand() % numLines + 1;
    trait = getLineAt(neuFileName, traitNum);
    if( trait.compare("Error") == 0 )
    {
        // Emit Error to MainWindow
        //emit errorCaught(lineReadErr);
        // setDefault, "Neat"
        trait = "Neat";
    }
    personalityTraits.append(", ");
    personalityTraits.append(trait);

    // Get Negative Trait
    QString negFileName(":/TextFiles/Negative.txt");
    numLines = getNumLines(negFileName);
    if( numLines == -1 )
    {
        // Emit Error to MainWindow
        //emit errorCaught(lineNumErr);
        // setDefault, 1
        numLines = 1;
    }
    traitNum = rand() % numLines + 1;
    trait = getLineAt(negFileName, traitNum);
    if( trait.compare("Error") == 0 )
    {
        // Emit Error to MainWindow
        //emit errorCaught(lineReadErr);
        // setDefault, "Neat"
        trait = "Neat";
    }
    personalityTraits.append(", ");
    personalityTraits.append(trait);

    return personalityTraits;
}



//////////////////////
// Getters and Setters
//////////////////////
string Generator::getsetName(bool setFlag, string toSet)
{
    if(setFlag)
    {
        name = toSet;
    }
    return name;
}

int Generator::getsetRace(bool setFlag, int toSet)
{
    if(setFlag)
    {
        race = toSet;
    }
    return race;
}

int Generator::getsetClass(bool setFlag, int toSet)
{
    if(setFlag)
    {
        charClass = toSet;
    }
    return charClass;
}

array<int, 2> Generator::getsetAlign(bool setFlag, array<int, 2>* toSet)
{
    if(setFlag)
    {
        alignment = *toSet;
    }
    return alignment;
}

int Generator::getsetLevel(bool setFlag, int toSet)
{
    if(setFlag)
    {
        level = toSet;
    }
    return level;
}


array<int, 6> Generator::getsetStats(bool setFlag, array<int, 6> *toSet)
{
    if(setFlag)
    {
        stats = *toSet;
    }
    return stats;
}

int Generator::getsetHP(bool setFlag, int toSet)
{
    if(setFlag)
    {
        hp = toSet;
    }
    return hp;
}

QString Generator::getsetPerson(bool setFlag, QString toSet)
{
    if(setFlag)
    {
        personality = toSet;
    }
    return personality;
}

QString Generator::getPersonTrait(int trait)
{
    QString pTrait = personality;
    QString ret = pTrait.section(',', trait, trait);
    ret.replace(" ", "");
    return ret;
}

int Generator::getGenID(bool setFlag, int toSet)
{
    if(setFlag)
    {
        ID = toSet;
    }
    return ID;
}

int Generator::checkId(int id)
{
    map<int, Generator>::iterator it;
    for( it = availableGens.begin(); it != availableGens.end(); it++ )
    {
        if(it->first == id)
        {
            id++;
            return checkId(id);
        }
    }
    return id;
}



void deleteGen(int toDel)
{
    // remove generator from map
    availableGens.erase(toDel);
}


//////////////////////
// Database Access
//////////////////////
int saveGens()
{
    map<int, Generator>::iterator it;
    for( it=availableGens.begin(); it != availableGens.end(); it++)
    {
        Generator toSave = it->second;
        if( saveGenerator(toSave) == -1 )
        {
            return -1;
        }
    }
    return 0;
}

int saveGenerator(Generator toSave)
{
    sqlite3* db;

    QDir databaseDir = getlogDir();
    QString database = databaseDir.filePath("data.db");
    QByteArray ba = database.toLocal8Bit();
    const char *data = ba.data();

    int success = sqlite3_open(data, &db);
    if (success)
    {
        // ErrorCode 1215
        QString error = "Cannot open database: ";
        error.append(QString::fromStdString(sqlite3_errmsg(db)));
        logError(gDbErr, error);

        return -1;
        //printf("Cannot open database %s\n", sqlite3_errmsg(db));
    }

    int returnCode;

    // 15 values to add
    const char* sql = "INSERT INTO NPC (ID, NAME, RACEID, CLASSID, ALIGN, PERPOS, PERNEU, PERNEG, LEVEL, HP, STR, DEX, CON, INT, WIS, CHAR) "\
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"\
    "ON CONFLICT(ID) DO UPDATE SET "\
    "NAME=excluded.name, RACEID=excluded.RACEID, CLASSID=excluded.CLASSID, ALIGN=excluded.ALIGN,"\
    "PERPOS=excluded.PERPOS, PERNEU=excluded.PERNEU, PERNEG=excluded.PERNEG, LEVEL=excluded.LEVEL, HP=excluded.HP,"\
    "STR=excluded.STR, DEX=excluded.DEX, CON=excluded.CON, INT=excluded.INT, WIS=excluded.WIS, CHAR=excluded.CHAR;";

    sqlite3_stmt* insert_stmt = NULL;
    returnCode = sqlite3_prepare_v2(db, sql, -1, &insert_stmt, NULL);
    if (returnCode != SQLITE_OK)
    {
        // ErrorCode 1216
        QString error = "Failed to prepare insert statement 'INSERT INTO NPC' (";
        error.append(QString::number(returnCode));
        error.append("): ");
        error.append(QString::fromStdString(sqlite3_errmsg(db)));
        logError(genFailPrep, error);
        //printf("Failed to prepare insert statement %s (%i): %s\n", sql, returnCode, sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }
    else
    {
        // Bind values (1 to 14 index)
        returnCode = sqlite3_bind_int(insert_stmt, 1, toSave.getGenID());
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1217
            QString error = "Failed bind ";
            error.append(QString::number(1));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(genFailBind, error);
            //printf("Failed bind %d, (%i): \n", 1, returnCode);
            return -1;
        }

        string cName = toSave.getsetName();
        char* name = &cName[0];
        returnCode = sqlite3_bind_text(insert_stmt, 2, name, sizeof(toSave.getsetName())+5, NULL);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1217
            QString error = "Failed bind ";
            error.append(QString::number(2));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(genFailBind, error);
            //printf("Failed bind %d, (%i): \n", 2, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 3, toSave.getsetRace());
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1217
            QString error = "Failed bind ";
            error.append(QString::number(3));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(genFailBind, error);
            //printf("Failed bind %d, (%i): \n", 3, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 4, toSave.getsetClass());
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1217
            QString error = "Failed bind ";
            error.append(QString::number(4));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(genFailBind, error);
            //printf("Failed bind %d, (%i): \n", 4, returnCode);
            return -1;
        }

        int align = (toSave.getsetAlign()[0] * 3) + toSave.getsetAlign()[1];
        returnCode = sqlite3_bind_int(insert_stmt, 5, align);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1217
            QString error = "Failed bind ";
            error.append(QString::number(5));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(genFailBind, error);
            //printf("Failed bind %d, (%i): \n", 5, returnCode);
            return -1;
        }

        string personality = toSave.getPersonTrait(0).toStdString();
        char* p = &personality[0];
        returnCode = sqlite3_bind_text(insert_stmt, 6, p, sizeof(personality)+4, NULL);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1217
            QString error = "Failed bind ";
            error.append(QString::number(6));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(genFailBind, error);
            //printf("Failed bind %d, (%i): \n", 6, returnCode);
            return -1;
        }

        string nality = toSave.getPersonTrait(1).toStdString();
        char* n = &nality[0];
        returnCode = sqlite3_bind_text(insert_stmt, 7, n, sizeof(personality)+4, NULL);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1217
            QString error = "Failed bind ";
            error.append(QString::number(7));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(genFailBind, error);
            //printf("Failed bind %d, (%i): \n", 7, returnCode);
            return -1;
        }

        string negality = toSave.getPersonTrait(2).toStdString();
        char* neg = &negality[0];
        returnCode = sqlite3_bind_text(insert_stmt, 8, neg, sizeof(personality)+4, NULL);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1217
            QString error = "Failed bind ";
            error.append(QString::number(8));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(genFailBind, error);
            //printf("Failed bind %d, (%i): \n", 8, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 9, toSave.getsetLevel());
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1217
            QString error = "Failed bind ";
            error.append(QString::number(9));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(genFailBind, error);
            //printf("Failed bind %d, (%i): \n", 9, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 10, toSave.getsetHP());
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1217
            QString error = "Failed bind ";
            error.append(QString::number(10));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(genFailBind, error);
            //printf("Failed bind %d, (%i): \n", 10, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 11, toSave.getsetStats()[0]);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1217
            QString error = "Failed bind ";
            error.append(QString::number(11));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(genFailBind, error);
            //printf("Failed bind %d, (%i): \n", 11, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 12, toSave.getsetStats()[1]);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1217
            QString error = "Failed bind ";
            error.append(QString::number(12));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(genFailBind, error);
            //printf("Failed bind %d, (%i): \n", 12, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 13, toSave.getsetStats()[2]);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1217
            QString error = "Failed bind ";
            error.append(QString::number(13));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(genFailBind, error);
            //printf("Failed bind %d, (%i): \n", 13, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 14, toSave.getsetStats()[3]);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1217
            QString error = "Failed bind ";
            error.append(QString::number(14));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(genFailBind, error);
            //printf("Failed bind %d, (%i): \n", 14, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 15, toSave.getsetStats()[4]);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1217
            QString error = "Failed bind ";
            error.append(QString::number(15));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(genFailBind, error);
            //printf("Failed bind %d, (%i): \n", 15, returnCode);
            return -1;
        }

        returnCode = sqlite3_bind_int(insert_stmt, 16, toSave.getsetStats()[5]);
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1217
            QString error = "Failed bind ";
            error.append(QString::number(16));
            error.append(", ");
            error.append(QString::number(returnCode));
            logError(genFailBind, error);
            //printf("Failed bind %d, (%i): \n", 16, returnCode);
            return -1;
        }

        returnCode = sqlite3_step(insert_stmt);
        if (returnCode != SQLITE_DONE)
        {
            // ErrorCode 1218
            QString error = "Insert stmt did not return DONE ";
            error.append(QString::number(returnCode));
            error.append(": ");
            error.append(QString::fromStdString(sqlite3_errmsg(db)));
            logError(genFailBind, error);
            //printf("Insert statement did not return DONE (%i): %s\n", returnCode, sqlite3_errmsg(db));
            return -1;
        }

        sqlite3_finalize(insert_stmt);

        sqlite3_close(db);
        return 0;
    }
}

int sqlToGen(void* data, int argc, char** argv, char** azColName)
{
    //ID=0, Name=1, Race/Class/Align=2-4, Person=5, Lvl/Hp/Stats/Sub 6-14

    string name = argv[1];
    string posPerson = argv[5];
    string neuPerson = argv[6];
    string negPerson = argv[7];

    int ID;
    sscanf(argv[0], "%d", &ID);

    Generator newChar = Generator(ID);

    int rca[3];
    for(int i=2; i<5; i++)
    {
        sscanf(argv[i], "%d", &rca[i-2]);
    }

    int endValues[8];
    for( int i=8; i<argc; i++ )
    {
        sscanf(argv[i], "%d", &endValues[i-8]);
    }

    //ID=0, Name=1, Race/Class/Align=2-4, Person=5, Lvl/Hp/Stats/Sub 6-14

    newChar.getsetName(SET, name);
    newChar.getsetRace(SET, rca[0]);
    newChar.getsetClass(SET, rca[1]);
    int morality = rca[2]/3;
    int belief = rca[2]%3;
    array<int, 2> align = {morality, belief};
    newChar.getsetAlign(SET, &align);
    QString personality;
    personality.append(QString::fromStdString(posPerson));
    personality.append(", ");
    personality.append(QString::fromStdString(neuPerson));
    personality.append(", ");
    personality.append(QString::fromStdString(negPerson));
    personality.append(", ");
    newChar.getsetPerson(SET, personality);
    array<int, 6> stats;
    try {
        newChar.getsetLevel(SET, endValues[0]);
        newChar.getsetHP(SET, endValues[1]);
        stats = {endValues[2], endValues[3], endValues[4], endValues[5], endValues[6], endValues[7]};
    }  catch (...) {
        //ErrorCode 1117
        QString error = "Could not generate NPC from sql: ";
        error.append(QString::number(ID));
        logError(GenCreateErr, error);
        return -1;
    }

    newChar.getsetStats(SET, &stats);
    availableGens.insert(pair<int, Generator>(newChar.getGenID(), newChar));

    return 0;
}

int readGenerators()
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
        logError(genOpenErr, error);
        //printf("Cannot open database %s\n", sqlite3_errmsg(db));
        return -1;
    }

    int returnCode;
    char *zErrMsg;

    const char* select = "SELECT * from NPC";
    returnCode = sqlite3_exec(db, select, sqlToGen, 0, &zErrMsg);

    if( returnCode != SQLITE_OK )
    {
        // ErrorCode 1219
        QString error = "Failed to read gens from database: ";
        error.append(QString::fromStdString(zErrMsg));
        logError(genFailRead, error);
        //printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }

    sqlite3_close(db);
    return 0;
}

void removeFromSQL(Generator toRemove)
{
    int returnCode;
    const char* del = "DELETE FROM NPC "\
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
        // ErrorCode 1215
        printf("Cannot open database%s\n", sqlite3_errmsg(db));
    }

    returnCode = sqlite3_prepare_v2(db, del, -1, &insert_stmt, NULL);
    if(returnCode != SQLITE_OK)
    {
        // ErrorCode 1216
        printf("Failed to prepare delete statement %s (%i): %s\n", del, returnCode, sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    returnCode = sqlite3_bind_int(insert_stmt, 1, toRemove.getGenID());
    if( returnCode != SQLITE_OK )
    {
        // ErrorCode 1217
        printf("Failed bind %d, (%i): \n", 1, returnCode);
    }

    returnCode = sqlite3_step(insert_stmt);
    if (returnCode != SQLITE_DONE)
    {
        // ErrorCode 1218
        printf("Delete statement did not return DONE (%i): %s\n", returnCode, sqlite3_errmsg(db));
    }

    sqlite3_finalize(insert_stmt);

    sqlite3_close(db);
}

void removeAllFromSQL()
{
    int returnCode;
    const char* del = "DELETE FROM NPC "\
                        "WHERE ID = ?;";
    sqlite3_stmt* insert_stmt = NULL;

    map<int, Generator>::iterator it;
    for( it = availableGens.begin(); it != availableGens.end(); it++)
    {
        sqlite3* db;

        QDir databaseDir = getlogDir();
        QString database = databaseDir.filePath("data.db");
        QByteArray ba = database.toLocal8Bit();
        const char *data = ba.data();

        int success = sqlite3_open(data, &db);
        if (success)
        {
            // ErrorCode 1215
            printf("Cannot open database %s\n", sqlite3_errmsg(db));
        }

        returnCode = sqlite3_prepare_v2(db, del, -1, &insert_stmt, NULL);
        if (returnCode != SQLITE_OK)
        {
            //ErrorCode 1216
            printf("Failed to prepare delete statement %s (%i): %s\n", del, returnCode, sqlite3_errmsg(db));
            sqlite3_close(db);
        }

        returnCode = sqlite3_bind_int(insert_stmt, 1, it->first );
        if( returnCode != SQLITE_OK )
        {
            // ErrorCode 1217
            printf("Failed bind %d, (%i): \n", 1, returnCode);
        }

        returnCode = sqlite3_step(insert_stmt);
        if (returnCode != SQLITE_DONE)
        {
            // ErrorCode 1218
            printf("Delete statement did not return DONE (%i): %s\n", returnCode, sqlite3_errmsg(db));
        }

        sqlite3_finalize(insert_stmt);

        sqlite3_close(db);
    }
}


