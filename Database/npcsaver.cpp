#include "npcsaver.h"

NpcSaver::NpcSaver()
{

}

int NpcSaver::saveAttributes()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    query.prepare("INSERT INTO NPC (ID, NAME, RACEID, CLASSID, ALIGN, "\
                  "PERPOS, PERNEU, PERNEG, LEVEL, HP, STR, DEX, CON, INT, "\
                  "WIS, CHAR) VALUES (:id, :name, :raceid, :classid, :align, "\
                  ":perpos, :perneu, :perneg, :level, :hp, :str, :dex, :con, :int, "\
                  ":wis, :char) ON CONFLICT(ID) DO UPDATE SET "\
                  "NAME=excluded.name, RACEID=excluded.RACEID, CLASSID=excluded.CLASSID, "\
                  "ALIGN=excluded.ALIGN,PERPOS=excluded.PERPOS, "\
                  "PERNEU=excluded.PERNEU, PERNEG=excluded.PERNEG, "\
                  "LEVEL=excluded.LEVEL, HP=excluded.HP,"\
                  "STR=excluded.STR, DEX=excluded.DEX, CON=excluded.CON, "\
                  "INT=excluded.INT, WIS=excluded.WIS, CHAR=excluded.CHAR;");
    map<unsigned long, Generator>::iterator it;
    for( it=availableGens.begin(); it!=availableGens.end(); it++)
    {
        Generator toSave = it->second;
        query.bindValue(":id", (int)toSave.getGenID());
        query.bindValue(":name", QString::fromStdString(toSave.getsetName()));
        query.bindValue(":raceid", toSave.getsetRace());
        query.bindValue(":classid", toSave.getsetClass());
        int align = (toSave.getsetAlign()[0] * 3) + toSave.getsetAlign()[1];
        query.bindValue(":align", align);
        query.bindValue(":perpos", toSave.getPersonTrait(0));
        query.bindValue(":perneu", toSave.getPersonTrait(1));
        query.bindValue(":perneg", toSave.getPersonTrait(2));
        query.bindValue(":level", toSave.getsetLevel());
        query.bindValue(":hp", toSave.getsetHP());
        query.bindValue(":str", toSave.getsetStats()[0]);
        query.bindValue(":dex", toSave.getsetStats()[1]);
        query.bindValue(":con", toSave.getsetStats()[2]);
        query.bindValue(":int", toSave.getsetStats()[3]);
        query.bindValue(":wis", toSave.getsetStats()[4]);
        query.bindValue(":char", toSave.getsetStats()[5]);
        if(!query.exec())
        {
            qDebug() << query.lastError().text();
            db.close();
            return -1;
        }
    }
    db.close();
    return 0;
}

int NpcSaver::readAttributes()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    query.exec("SELECT ID, NAME, RACEID, CLASSID, ALIGN, PERPOS, PERNEU "\
               "PERNEG, LEVEL, HP, STR, DEX, CON, INT, WIS, CHAR FROM NPC");
    while( query.next() )
    {
        Generator newGen;
        try{
            unsigned long id = query.value(0).toULongLong();
            string name = query.value(1).toString().toStdString();
            int raceId = query.value(2).toInt();
            int classId = query.value(3).toInt();
            int alignment = query.value(4).toInt();
            array<int, 2> align = {alignment/3, alignment%3};
            QString personality;
            personality.append(query.value(5).toString());
            personality.append(query.value(6).toString());
            personality.append(query.value(7).toString());
            int level = query.value(8).toInt();
            int hp = query.value(9).toInt();
            int str = query.value(10).toInt();
            int dex = query.value(11).toInt();
            int con = query.value(12).toInt();
            int intel = query.value(13).toInt();
            int wis = query.value(14).toInt();
            int chara = query.value(15).toInt();
            array<int, 6> stats = {str, dex, con, intel, wis, chara};
            newGen = Generator(id, name, raceId, classId, align, personality, level, hp, stats);
        } catch (...) {
            //Error
            return -1;
        }
        availableGens.insert(pair<int, Generator>(newGen.getGenID(), newGen));
        qDebug() << query.value(1).toString();
    }
    db.close();
    return 0;
}

void NpcSaver::removeAllAttributes()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    query.exec("DELETE FROM NPC");
    db.close();
}
