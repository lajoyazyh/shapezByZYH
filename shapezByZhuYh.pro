QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    block.cpp \
    conveyorbelt.cpp \
    cutter.cpp \
    device.cpp \
    gamescene.cpp \
    main.cpp \
    mainscene.cpp \
    map.cpp \
    miner.cpp \
    ore.cpp \
    source.cpp \
    storescene.cpp \
    trashbin.cpp \
    upgradedialog.cpp

HEADERS += \
    Directions.h \
    block.h \
    conveyorbelt.h \
    cutter.h \
    device.h \
    gamescene.h \
    mainscene.h \
    map.h \
    miner.h \
    ore.h \
    ore_cut.h \
    source.h \
    storescene.h \
    trashbin.h \
    upgradedialog.h

FORMS += \
    gamescene.ui \
    mainscene.ui \
    storescene.ui \
    upgradedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
