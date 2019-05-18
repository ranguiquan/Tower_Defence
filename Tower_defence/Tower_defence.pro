#-------------------------------------------------
#
# Project created by QtCreator 2019-05-02T22:13:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tower_defence
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    scene.cpp \
    gameobject.cpp \
    tower.cpp \
    enemy.cpp \
    bullet.cpp \
    mypoint.cpp \
    tool.cpp \
    player.cpp \
    enemy1.cpp \
    enemy2.cpp \
    enemy3.cpp \
    enemy4.cpp \
    enemy5.cpp \
    enemy6.cpp \
    enemy7.cpp \
    enemy8.cpp \
    enemy9.cpp

HEADERS += \
        mainwindow.h \
    scene.h \
    config.h \
    gameobject.h \
    tower.h \
    enemy.h \
    bullet.h \
    mypoint.h \
    tool.h \
    player.h \
    enemy1.h \
    enemy2.h \
    enemy3.h \
    enemy4.h \
    enemy5.h \
    enemy6.h \
    enemy7.h \
    enemy8.h \
    enemy9.h

FORMS += \
        mainwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
