#-------------------------------------------------
#
# Project created by QtCreator 2015-12-30T20:09:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eAukcja
TEMPLATE = app


SOURCES += main.cpp\
        start.cpp

HEADERS  += start.h

FORMS    += start.ui

INCLUDEPATH += .
INCLUDEPATH += /usr/include/botan-1.10/
LIBS += -lbotan-1.10
#LIBPATH += /root/Pobrane/Botan/
CONFIG += c++11
