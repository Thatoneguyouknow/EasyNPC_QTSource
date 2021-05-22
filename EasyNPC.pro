QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Attributes/alignment.cpp \
    Attributes/class.cpp \
    Attributes/race.cpp \
    Attributes/stats.cpp \
    Helper_Functions/database.cpp \
    Helper_Functions/errorlog.cpp \
    Helper_Functions/racenames.cpp \
    charcard.cpp \
    classview.cpp \
    codederror.cpp \
    editchar.cpp \
    generator.cpp \
    main.cpp \
    mainwindow.cpp \
    newclass.cpp \
    Helper_Functions/personality.cpp \
    newrace.cpp \
    raceview.cpp \
    Helper_Functions/sqlite3.c

HEADERS += \
    Attributes/alignment.h \
    Attributes/class.h \
    Attributes/race.h \
    Attributes/stats.h \
    Helper_Functions/database.h \
    Helper_Functions/errorlog.h \
    Helper_Functions/racenames.h \
    charcard.h \
    classview.h \
    codederror.h \
    editchar.h \
    generator.h \
    mainwindow.h \
    newclass.h \
    Helper_Functions/personality.h \
    newrace.h \
    raceview.h \
    Helper_Functions/sqlite3.h

FORMS += \
    charcard.ui \
    classview.ui \
    codederror.ui \
    editchar.ui \
    mainwindow.ui \
    newclass.ui \
    newrace.ui \
    raceview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    Card.png \
    ErrorCodes \
    Negative.txt \
    Neutral.txt \
    Positive.txt

