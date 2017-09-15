include(../environment.pri)

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

HEADERS  += \
    mainwindow.h \
    addcontractwidget.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    addcontractwidget.cpp

FORMS += \
    mainwindow.ui \
    addcontractwidget.ui
