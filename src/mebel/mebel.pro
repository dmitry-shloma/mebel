include(../environment.pri)

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

HEADERS  += \
    mainwindow.h \
    addorderwidget.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    addorderwidget.cpp

FORMS += \
    mainwindow.ui \
    addorderwidget.ui
