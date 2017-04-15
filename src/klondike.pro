#-------------------------------------------------
#
# Project created by QtCreator 2017-04-06T19:33:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = klondike
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    deckview.cpp \
    Card.cpp \
    CardStacks.cpp \
    Error.cpp \
    cardview.cpp \
    remainingpackview.cpp \
    workingpackview.cpp \
    cardselection.cpp


HEADERS  += mainwindow.h \
    deckview.h \
    Card.hpp \
    CardStacks.hpp \
    Error.hpp \
    cardview.h \
    remainingpackview.h \
    workingpackview.h \
    cardselection.h

FORMS    += mainwindow.ui \
    deckview.ui \
    cardview.ui \
    remainingpackview.ui \
    workingpackview.ui \
    cardselection.ui

RESOURCES += \
    icons.qrc
