#-------------------------------------------------
#
# Project created by QtCreator 2017-04-06T19:33:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11

TARGET = hra2017
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
    cardselection.cpp \
    targetpackview.cpp \
    Command.cpp \
    Deck.cpp \
    Controller.cpp \
    View.cpp


HEADERS  += deckview.h \
    mainwindow.h \
    Card.hpp \
    CardStacks.hpp \
    Error.hpp \
    cardview.h \
    remainingpackview.h \
    workingpackview.h \
    cardselection.h \
    targetpackview.h \
    Deck.hpp \
    Command.hpp \
    View.hpp \
    Controller.hpp

FORMS    += mainwindow.ui \
    deckview.ui \
    cardview.ui \
    remainingpackview.ui \
    workingpackview.ui \
    cardselection.ui \
    targetpackview.ui

RESOURCES += \
    icons.qrc
