#-------------------------------------------------
#
# Project created by QtCreator 2015-04-10T10:40:00
#
#-------------------------------------------------
QT       += core gui serialport
QT += serialport
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CountTime
TEMPLATE = app


SOURCES += main.cpp\
        maincount.cpp \
    querytime.cpp

HEADERS  += maincount.h \
    querytime.h
