include(../qmake_helper.pri)

is_project_configured(): include(../environment.pri)

QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

HEADERS  += \
    mainwindow.h \
    orderwidget.h \
    customerinfowidget.h \
    orderinfowidget.h \
    settings.h \
    sqldatabasehelper.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    orderwidget.cpp \
    customerinfowidget.cpp \
    orderinfowidget.cpp

FORMS += \
    mainwindow.ui \
    orderwidget.ui \
    orderinfowidget.ui \
    customerinfowidget.ui
