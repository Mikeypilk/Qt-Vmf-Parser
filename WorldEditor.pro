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
    tests/brushtests.cpp \
    viewportscene.cpp \
    viewportview.cpp \
    map.cpp \
    tests/maptests.cpp \
    polygoniser.cpp \
    tests/polygontests.cpp

HEADERS  += mainwindow.h \
    tests/alltests.h \
    brush.h \
    tests/brushtests.h \
    viewportscene.h \
    viewportview.h \
    map.h \
    tests/maptests.h \
    polygoniser.h \
    tests/polygontests.h

FORMS    += mainwindow.ui

CONFIG += testcase
