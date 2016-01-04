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
    podprotokol1.cpp \
    oknoglowne.cpp \
    nowaaukcja.cpp \
    tcp.cpp \
    szyfrowanie.cpp \
    baza.cpp \
    gui.cpp \
    sterownik.cpp \
    podprotokol.cpp \
    zlozoferte.cpp \
    wybierzzwyciezce.cpp

HEADERS  += start.h \
    podprotokol1.h \
    oknoglowne.h \
    nowaaukcja.h \
    tcp.h \
    szyfrowanie.h \
    baza.h \
    gui.h \
    sterownik.h \
    podprotokol.h \
    zlozoferte.h \
    wybierzzwyciezce.h

FORMS    += start.ui \
    oknoglowne.ui \
    nowaaukcja.ui \
    zlozoferte.ui \
    wybierzzwyciezce.ui

INCLUDEPATH += .
INCLUDEPATH += /usr/include/botan-1.10/
LIBS += -lbotan-1.10
#LIBPATH += /root/Pobrane/Botan/
CONFIG += c++11

DISTFILES += \
    struktury

