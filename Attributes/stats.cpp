#include "stats.h"

int calcModifier(int abilityScore)
{
    if(abilityScore%2 == 1)
    {
        abilityScore -= 1;
    }
    int modifier = (abilityScore - 10)/2;
    return modifier;
}

int searchStats(string stat)
{
    map<int, string>::const_iterator it;
    for( it=statNames.begin(); it != statNames.end(); it++ )
    {
        if( it->second.compare(stat) == 0 )
        {
            return it->first;
        }
    }
    // Error check here
    return -1;
}

int searchHd(string hit)
{
    map<int, string>::const_iterator it;

    for( it=hitdieVals.begin(); it!=hitdieVals.end(); it++ )
    {
        if( it->second.compare(hit) == 0 )
        {
            return it->first;
        }
    }
    // Error check here
    return -1;
}

int getHdPos(int HitDie)
{
    for( int i=0; i < (int)hdNums.size(); i++ )
    {
        if( HitDie == hdNums[i] )
        {
            return i;
        }
    }
    // Error check here
    return -1;
}
