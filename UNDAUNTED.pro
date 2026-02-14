QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    agent.cpp \
    bfs.cpp \
    deck.cpp \
    dice.cpp \
    gameboard.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    playerinfo.cpp \
    scout.cpp \
    selectmap.cpp \
    sergeant.cpp \
    sniper.cpp

HEADERS += \
    Card.h \
    GameLogic.h \
    agent.h \
    bfs.h \
    deck.h \
    dice.h \
    gameboard.h \
    mainwindow.h \
    map.h \
    playerinfo.h \
    scout.h \
    selectmap.h \
    sergeant.h \
    sniper.h

FORMS += \
    gameboard.ui \
    mainwindow.ui \
    playerinfo.ui \
    selectmap.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    agents.qrc \
    cards.qrc \
    image/resource.qrc \
    image1.qrc \
    images.qrc \
    map.qrc








