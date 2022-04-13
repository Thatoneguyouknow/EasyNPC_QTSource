#include "classsaver.h"

ClassSaver::ClassSaver()
{

}

int ClassSaver::saveAttributes()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    query.prepare("INSERT OR IGNORE INTO CLASS (ID, NAME, HITDIE, "\
        "P1STAT, P2STAT, P3STAT, P4STAT, P5STAT, P6STAT, USERMADE) " \
        "VALUES (:id, :name, :hitdie, :p1stat, :p2stat, :p3stat, :p4stat, :p5stat,"\
        ":p6stat, :usermade) ON CONFLICT(ID) DO UPDATE SET "\
        "NAME=excluded.NAME, HITDIE=excluded.HITDIE, P1STAT=excluded.P1STAT, "\
        "P2STAT=excluded.P2STAT, P3STAT=excluded.P3STAT, P4STAT=excluded.P4STAT, "\
        "P5STAT=excluded.P5STAT, P6STAT=excluded.P6STAT, USERMADE=excluded.USERMADE;");

    map<int, Class>::iterator it;
    for( it=availableClasses.begin(); it!=availableClasses.end(); it++ )
    {
        Class toSave = it->second;
        query.bindValue(":id", toSave.getClassID());
        query.bindValue(":name", QString::fromStdString(toSave.getsetName()));
        query.bindValue(":hitdie", toSave.getsetHitDie());
        query.bindValue(":p1stat", toSave.getsetPriority()[0]);
        query.bindValue(":p2stat", toSave.getsetPriority()[1]);
        query.bindValue(":p3stat", toSave.getsetPriority()[2]);
        query.bindValue(":p4stat", toSave.getsetPriority()[3]);
        query.bindValue(":p5stat", toSave.getsetPriority()[4]);
        query.bindValue(":p6stat", toSave.getsetPriority()[5]);
        query.bindValue(":usermade", toSave.getsetUser());
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

int ClassSaver::readAttributes()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    query.exec("SELECT ID, NAME, HITDIE, P1STAT, P2STAT, P3STAT, "\
               "P4STAT, P5STAT, P6STAT, USERMADE FROM CLASS");
    while( query.next() )
    {
        Class newClass;
        try{
            int id = query.value(0).toInt();
            string name = query.value(1).toString().toStdString();
            int hitdie = query.value(2).toInt();
            array<int, 6> stats = {query.value(3).toInt(),
                                   query.value(4).toInt(),
                                   query.value(5).toInt(),
                                   query.value(6).toInt(),
                                   query.value(7).toInt(),
                                   query.value(8).toInt()};
            int user_created = query.value(9).toInt();
            newClass = Class(id, name, hitdie, stats, user_created);
        } catch (...) {
            // Error
            return -1;
        }
        availableClasses.insert(pair<int, Class>(newClass.getClassID(), newClass));
        qDebug() << query.value(1).toString();
    }
    db.close();
    return 0;
}

void ClassSaver::removeAllAttributes()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    query.exec("DELETE FROM CLASS");
    db.close();
}
