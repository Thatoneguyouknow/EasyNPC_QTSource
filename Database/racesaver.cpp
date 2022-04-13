#include "racesaver.h"

RaceSaver::RaceSaver()
{

}

int RaceSaver::saveAttributes()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    query.prepare("INSERT OR IGNORE INTO RACE (ID, NAME, ASIPSTAT, ASISSTAT, "\
                  "ASIPVAL, ASISVAL, AGEMAX, AGEMIN, NAMETYPE)" \
                  "VALUES (:id, :name, :asipstat, :asisstat, :asipval, :asisval,"\
                  ":agemax, :agemin, :nametype)"\
                  "ON CONFLICT(ID) DO UPDATE SET "\
                  "NAME=excluded.NAME, ASIPSTAT=excluded.ASIPSTAT, "\
                  "ASISSTAT=excluded.ASISSTAT, ASIPVAL=excluded.ASIPVAL, "\
                  "ASISVAL=excluded.ASISVAL, AGEMAX=excluded.AGEMAX, "\
                  "AGEMIN=excluded.AGEMIN, NAMETYPE=excluded.NAMETYPE;");

    map<int, Race>::iterator it;
    for( it=availableRaces.begin(); it!=availableRaces.end(); it++ )
    {
        Race toSave = it->second;
        query.bindValue(":id", toSave.getIdentifier());
        query.bindValue(":name", QString::fromStdString(toSave.getsetName()));
        query.bindValue(":asipstat", toSave.getsetPrimStat());
        query.bindValue(":asisstat", toSave.getsetSecStat());
        query.bindValue(":asipval", toSave.getsetPrimVal());
        query.bindValue(":asisval", toSave.getsetSecVal());
        query.bindValue(":agemax", toSave.getsetMaxAge());
        query.bindValue(":agemin", toSave.getsetMinAge());
        query.bindValue(":nametype", toSave.getsetNameType());
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

int RaceSaver::readAttributes()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    query.exec("SELECT ID, NAME,  ASIPSTAT, ASISSTAT, "\
               "ASIPVAL, ASISVAL, AGEMAX, AGEMIN, NAMETYPE FROM RACE");
    while( query.next() )
    {
        Race newRace;
        try{
            int id = query.value(0).toInt();
            string name = query.value(1).toString().toStdString();
            int pstat = query.value(2).toInt();
            int sstat = query.value(3).toInt();
            int pval = query.value(4).toInt();
            int sval = query.value(5).toInt();
            int agemax = query.value(6).toInt();
            int agemin = query.value(7).toInt();
            int nametype = query.value(8).toInt();
            newRace = Race(id, name, pstat, sstat, pval, sval, agemax, agemin, nametype);
        } catch (...) {
            //Error
            return -1;
        }
        availableRaces.insert(pair<int, Race>(newRace.getIdentifier(), newRace));
        qDebug() << query.value(1).toString();
    }
    db.close();
    return 0;
}

void RaceSaver::removeAllAttributes()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    query.exec("DELETE FROM RACE");
    db.close();
}
