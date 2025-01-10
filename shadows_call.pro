QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    enemy.cpp \
    frog.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    player.cpp
    moc_enemy.cppqmak

HEADERS += \
    enemy.h \
    frog.h \
    mainwindow.h \
    map.h \
    player.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    enemy.qrc \
    frog.qrc \
    player.qrc \
    player2.qrc \
    tree.qrc
