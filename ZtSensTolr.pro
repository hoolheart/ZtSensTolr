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
    datamodel.cpp \
    tableview.cpp \
    createprodialog.cpp \
    startupdialog.cpp \
    addcomponentdialog.cpp \
    componentdialog.cpp \
    stmath.cpp \
    addfeaturedialog.cpp

HEADERS  += mainwindow.h \
    tolrdata.h \
    ZtTable.h \
    datamodel.h \
    ztlogger.h \
    tableview.h \
    createprodialog.h \
    startupdialog.h \
    addcomponentdialog.h \
    componentdialog.h \
    stmath.h \
    addfeaturedialog.h

FORMS    += mainwindow.ui \
    createprodialog.ui \
    startupdialog.ui \
    addcomponentdialog.ui \
    componentdialog.ui \
    addfeaturedialog.ui

OTHER_FILES += \
    README.md \
    tolrdata.xml
