#-------------------------------------------------
#
# Project created by QtCreator 2016-11-19T22:56:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projet
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
    convert.cpp \
    edit.cpp

HEADERS  += mainwindow.h \
    convert.h \
    include.h \
    edit.h

# The following lines tells Qmake to use pkg-config for opencv
QT_CONFIG -= no-pkg-config
CONFIG  += link_pkgconfig
PKGCONFIG += opencv
