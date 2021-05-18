//
//  Stats.cpp
//  Dnd
//
//  Created by Benjamin Peterson on 2/5/21.
//

#include "Stats.hpp"

int calcModifier(int abilityScore)
{
    if(abilityScore%2 == 1)
    {
        abilityScore -= 1;
    }
    // The checks below and "abilityScore != 1" are checked by the Generator when making ability scores
    /*if(abilityScore > 30)
    {
        abilityScore = 30;
    }
    if(abilityScore < 8)
    {
        abilityScore = 8;
    }*/

    int modifier = (abilityScore - 10)/2;
    return modifier;
}

int searchStats(string stat)
{
    map<int, string>::const_iterator it;
    for(it=statNames.begin(); it!=statNames.end(); it++)
    {
        if(it->second.compare(stat) == 0)
        {
            return it->first;
        }
    }
    QString error = "Stat not found: ";
    error.append(QString::fromStdString(stat));
    logError(statNotFound, error, getlogDir());
    return -1;
}

int searchHd(string hit)
{
    map<int, string>::const_iterator it;

    for( it=hitdieVals.begin(); it!=hitdieVals.end(); it++ )
    {
        if(it->second.compare(hit) == 0)
        {
            return it->first;
        }
    }
    QString error = "HitDie not found: ";
    error.append(QString::fromStdString(hit));
    logError(hdNotFound, error, getlogDir());
    return -1;
}


int getHdPos(int HitDie)
{
    for(int i=0; i<(int)hdNums.size(); i++)
    {
        if(HitDie == hdNums[i])
        {
            return i;
        }
    }
    QString error = "HitDie Position not found: ";
    error.append(QString::number(HitDie));
    logError(hdPosNotFound, error, getlogDir());
    return -1;
}
