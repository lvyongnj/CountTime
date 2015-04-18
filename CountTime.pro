#-------------------------------------------------
#
# Project created by QtCreator 2015-04-14T10:08:07
#
#-------------------------------------------------
QT       += core gui serialport
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CountTime
TEMPLATE = app


SOURCES += main.cpp\
    window.cpp \
    currenttime.cpp \
    historyTime.cpp \
    serialcom.cpp \
    doCount.cpp

HEADERS  += \
    window.h \
    currenttime.h \
    historyTime.h \
    serialcom.h \
    doCount.h
