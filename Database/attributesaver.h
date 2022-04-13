#ifndef ATTRIBUTESAVER_H
#define ATTRIBUTESAVER_H

#include "Helper_Functions/sqlite3.h"

#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <array>

#include <QString>
#include <QtSql>

#include "Attributes/stats.h"
#include "Database/dbConnection.h"

class AttributeSaver
{
public:
    AttributeSaver();
    ~AttributeSaver();
    virtual int saveAttributes() = 0;
    virtual int readAttributes() = 0;
    virtual void removeAllAttributes() {};
};

#endif // ATTRIBUTESAVER_H
