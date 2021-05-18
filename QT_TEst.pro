TEMPLATE = app
TARGET = EasyNPC

QT = core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    Helper_Functions/Database.cpp \
    Helper_Functions/Personality.cpp \
    Helper_Functions/RaceNames.cpp \
    Attributes/Alignment.cpp \
    Attributes/Class.cpp \
    Attributes/Race.cpp \
    Attributes/Stats.cpp \
    Helper_Functions/errorlog.cpp \
    characterview.cpp \
    charcard.cpp \
    classview.cpp \
    codederror.cpp \
    editchar.cpp \
    generator.cpp \
    main.cpp \
    mainwindow.cpp \
    newclass.cpp \
    newrace.cpp \
    raceview.cpp

CONFIG += sdk_no_version_check

RESOURCES += Resources/resources.qrc

HEADERS += \
    Helper_Functions/Database.hpp \
    Helper_Functions/Personality.hpp \
    Helper_Functions/RaceNames.hpp \
    Attributes/Alignment.hpp \
    Attributes/Class.hpp \
    Attributes/Race.hpp \
    Attributes/Stats.hpp \
    Helper_Functions/errorlog.h \
    characterview.h \
    charcard.h \
    classview.h \
    codederror.h \
    editchar.h \
    generator.hpp \
    mainwindow.h \
    newclass.h \
    newrace.h \
    raceview.h

LIBS += -lsqlite3

DISTFILES += \
    ErrorCodes \
    Helper_Functions/copyData.sh \
    Resources/Negative.txt \
    Resources/Neutral.txt \
    Resources/Positive.txt \
    Resources/download.png \
    Resources/download.xcf \
    Resources/download.xpm \
    Resources/pixil-frame-0.png \
    copyData.sh

FORMS += \
    characterview.ui \
    charcard.ui \
    classview.ui \
    codederror.ui \
    editchar.ui \
    mainwindow.ui \
    newclass.ui \
    newrace.ui \
    raceview.ui
