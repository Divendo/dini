#-------------------------------------------------
#
# Project created by QtCreator 2010-11-27T12:29:59
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = dini
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += example.cpp \
    inifile.cpp \
    inivalue.cpp \
    dini_private.cpp \
    inisection.cpp

HEADERS += \
    inifile.h \
    inivalue.h \
    dini_private.h \
    inisection.h \
    dini.h
