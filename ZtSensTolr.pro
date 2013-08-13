#-------------------------------------------------
#
# Project created by QtCreator 2013-06-26T10:55:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZtSensTolr
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tolrdata.cpp \
    ZtTable.cpp \
    datamodel.cpp

HEADERS  += mainwindow.h \
    tolrdata.h \
    ZtTable.h \
    datamodel.h \
    ztlogger.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    README.md \
    tolrdata.xml
