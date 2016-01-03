#-------------------------------------------------
#
# Project created by QtCreator 2015-12-30T20:09:00
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eAukcja
TEMPLATE = app


SOURCES += main.cpp\
    start.cpp \
    tcp.cpp \
    szyfrowanie.cpp \
    baza.cpp \
    gui.cpp \
    sterownik.cpp \
    podprotokol1.cpp \
    podprotokol.cpp

HEADERS  += start.h \
    tcp.h \
    szyfrowanie.h \
    baza.h \
    gui.h \
    sterownik.h \
    podprotokol1.h \
    podprotokol.h

FORMS    += start.ui

INCLUDEPATH += .
INCLUDEPATH += /usr/include/botan-1.10/
LIBS += -lbotan-1.10
#LIBPATH += /root/Pobrane/Botan/
CONFIG += c++11

