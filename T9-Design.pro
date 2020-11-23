#-------------------------------------------------
#
# Project created by QtCreator 2018-10-16T09:50:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = T9-Design
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
    piece.cpp \
    Player.cpp \
    tile.cpp \
    board.cpp \
    testBoard.cpp \
    startwindow.cpp \
    boardwindow.cpp \
    sidewidget.cpp \
    pausewindow.cpp \
    optionwindow.cpp \
    validmove.cpp \
    AI.cpp

HEADERS += \
    board.h \
    piece.h \
    Player.h \
    tile.h \
    startwindow.h \
    boardwindow.h \
    sidewidget.h \
    pausewindow.h \
    optionwindow.h \
    AI.h

FORMS += \
    startwindow.ui \
    boardwindow.ui \
    sidewidget.ui \
    pausewindow.ui \
    optionwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc \
    sound.qrc
