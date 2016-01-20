#-------------------------------------------------
#
# Project created by QtCreator 2015-12-30T20:09:00
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eAukcjaSerwer
TEMPLATE = app


SOURCES += main.cpp\
    podprotokoly/podprotokol1.cpp \
    utils/tcp.cpp \
    utils/szyfrowanie.cpp \
    utils/baza.cpp \
    podprotokoly/podprotokol.cpp \
    podprotokoly/podprotokol2.cpp \
    podprotokoly/podprotokol3.cpp \
    podprotokoly/podprotokol4.cpp \
    sterownik/sterownik.cpp \
    utils/proxytcp.cpp \
    utils/tcpserwer.cpp \
    utils/uzytkownik.cpp \
    utils/aukcja.cpp

HEADERS  += podprotokoly/podprotokol1.h \
    utils/tcp.h \
    utils/szyfrowanie.h \
    utils/baza.h \
    podprotokoly/podprotokol.h \
    podprotokoly/podprotokol2.h \
    podprotokoly/podprotokol3.h \
    podprotokoly/podprotokol4.h \
    sterownik/sterownik.h \
    utils/proxytcp.h \
    utils/tcpserwer.h \
    utils/uzytkownik.h \
    utils/aukcja.h

#FORMS    += gui/start.ui \

INCLUDEPATH +=/usr/include/crypto++
INCLUDEPATH += /usr/include/botan-1.10/
LIBS += -lcrypto++
LIBS += -lbotan-1.10
#LIBPATH += /root/Pobrane/Botan/
CONFIG += c++11

DISTFILES += \
    struktury

