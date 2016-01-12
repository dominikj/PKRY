#-------------------------------------------------
#
# Project created by QtCreator 2015-12-30T20:09:00
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KeyGen
TEMPLATE = app


SOURCES += main.cpp\
    utils/szyfrowanie.cpp \

HEADERS  += utils/szyfrowanie.h \


INCLUDEPATH += .
INCLUDEPATH += /usr/include/botan-1.10/
LIBS += -lbotan-1.10
#LIBPATH += /root/Pobrane/Botan/
CONFIG += c++11

DISTFILES += \
    struktury

