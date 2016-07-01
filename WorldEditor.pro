#-------------------------------------------------
#
# Project created by QtCreator 2016-07-01T17:10:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets testlib

TARGET = WorldEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        tests/alltests.cpp \
    brush.cpp \
    tests/brushtests.cpp

HEADERS  += mainwindow.h \
        tests/alltests.h \
    brush.h \
    tests/brushtests.h

FORMS    += mainwindow.ui

CONFIG += testcase
