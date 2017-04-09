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
    card.cpp \
    CardStacks.cpp \
    Error.cpp


HEADERS  += mainwindow.h \
    deckview.h \
    card.hpp \
    CardStacks.hpp \
    Error.hpp

FORMS    += mainwindow.ui \
    deckview.ui
