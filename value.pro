#-------------------------------------------------
#
# Project created by QtCreator 2025-05-16T19:57:48
#
#-------------------------------------------------

QT       += core gui concurrent
QT       += axcontainer
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = value
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    rulerbar.cpp \
    value_type.cpp \
    excel\excelreader.cpp \
    dataBase\mysqldatabase.cpp \
    thread\databaseworker.cpp \
    excel/spreadsheet.cpp \
    dataBase/sqlserverhandler.cpp \
    distort/distortmainwindow.cpp \
    distort/distortsubwindow1.cpp \
    distort/distortsubwindow2.cpp

HEADERS += \
        mainwindow.h \
    rulerbar.h \
    value_type.h \
    excel\excelreader.h \
    dataBase\mysqldatabase.h \
    thread\databaseworker.h \
    excel/spreadsheet.h \
    dataBase/sqlserverhandler.h \
    distort/distortmainwindow.h \
    distort/distortsubwindow1.h \
    distort/distortsubwindow2.h

FORMS += \
        mainwindow.ui \
    distort/distortmainwindow.ui \
    distort/distortsubwindow1.ui \
    distort/distortsubwindow2.ui

RESOURCES += \
    res.qrc

DISTFILES += \
    logo.rc

RC_FILE += logo.rc

