#-------------------------------------------------
#
# Project created by QtCreator 2016-09-27T17:35:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tp1
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp

HEADERS  += mainwindow.h

# The following lines tells Qmake to use pkg-config for opencv
QT_CONFIG -= no-pkg-config
CONFIG  += link_pkgconfig
PKGCONFIG += opencv
