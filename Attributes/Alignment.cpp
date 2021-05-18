//
//  Alignment.cpp
//  Dnd
//
//  Created by Benjamin Peterson on 1/22/21.
//
#include "Alignment.hpp"


////////////////
//// THIS FILE NO LONGER IN USE
/// ////////////

// Belief - lawful, neutral, chaotic
// Morality - good, neutral, evil
// These two files will be used only to convert the int alignments to a string

//TODO: Should probably do this better, maybe a map?
/*string printAlign(int belief, int morality)
{
    string beliefStr = "PLACEHOLDER";
    switch(belief)
    {
        case 0:
            beliefStr = "Lawful ";
            break;
        case 1:
            beliefStr = "Neutral ";
            break;
        case 2:
            beliefStr = "Chaotic ";
            break;
        default:
            QString error = "Belief val does not exist: ";
            error.append(QString::number(belief));
            logError(beliefExist, error, getlogDir());
            // default val 0
            beliefStr = "Lawful ";
            break;
    }
    string moralStr = "PLACEHOLDER";
    switch(morality)
    {
        case 0:
            moralStr = "Good";
            break;
        case 1:
            moralStr = "Neutral";
            break;
        case 2:
            moralStr = "Evil";
            break;
        default:
        // ErrorCode 1115
            moralStr = "Error";
            break;
    }
    
    if( belief == morality && morality == 1 )
    {
        beliefStr = "True ";
    }

    string align = beliefStr + moralStr;
    return align;
}*/
