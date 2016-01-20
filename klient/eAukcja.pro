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
    gui/start.cpp \
    podprotokoly/podprotokol1.cpp \
    gui/oknoglowne.cpp \
    gui/nowaaukcja.cpp \
    utils/tcp.cpp \
    utils/szyfrowanie.cpp \
    utils/baza.cpp \
    gui/gui.cpp \
    podprotokoly/podprotokol.cpp \
    gui/zlozoferte.cpp \
    gui/wybierzzwyciezce.cpp \
    podprotokoly/podprotokol2.cpp \
    podprotokoly/podprotokol3.cpp \
    podprotokoly/podprotokol4.cpp \
    sterownik/oczekujzwyciezcy.cpp \
    sterownik/sterownik.cpp \
    utils/proxytcp.cpp \
    utils/aukcja.cpp

HEADERS  += gui/start.h \
    podprotokoly/podprotokol1.h \
    gui/oknoglowne.h \
    gui/nowaaukcja.h \
    utils/tcp.h \
    utils/szyfrowanie.h \
    utils/baza.h \
    gui/gui.h \
    podprotokoly/podprotokol.h \
    gui/zlozoferte.h \
    gui/wybierzzwyciezce.h \
    podprotokoly/podprotokol2.h \
    podprotokoly/podprotokol3.h \
    podprotokoly/podprotokol4.h \
    sterownik/oczekujzwyciezcy.h \
    sterownik/sterownik.h \
    utils/proxytcp.h \
    utils/aukcja.h

FORMS    += gui/start.ui \
    gui/oknoglowne.ui \
    gui/nowaaukcja.ui \
    gui/zlozoferte.ui \
    gui/wybierzzwyciezce.ui

INCLUDEPATH +=/usr/include/crypto++
INCLUDEPATH += /usr/include/botan-1.10/
LIBS += -lbotan-1.10
LIBS += -lcrypto++
#QMAKE_CXXFLAGS += -isystem /usr/include/crypto++
#QMAKE_CXXFLAGS += -isystem /usr/include/botan-1.10
QMAKE_CXXFLAGS += -Wno-deprecated-declarations
#LIBPATH += /root/Pobrane/Botan/
CONFIG += c++11
DISTFILES += \
    struktury

