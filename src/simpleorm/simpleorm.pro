include(../environment.pri)

QT += core sql
QT -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib

CONFIG += static

DEFINES += SIMPLEORM_LIBRARY

HEADERS += \
    simpleorm.h \
    simpleorm_global.h

SOURCES += \
    simpleorm.cpp
