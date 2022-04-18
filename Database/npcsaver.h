#ifndef NPCSAVER_H
#define NPCSAVER_H

#include "attributesaver.h"
#include "generator.h"

class NpcSaver : public AttributeSaver
{
public:
    NpcSaver();
    int saveAttributes();
    int readAttributes();
    void removeAllAttributes();
};

#endif // NPCSAVER_H
