#-------------------------------------------------
#
# Project created by QtCreator 2016-11-19T22:56:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projet
TEMPLATE = app


SOURCES += src/main.cpp \
           src/mainwindow.cpp \
           src/convert.cpp \
           src/edit.cpp \
           src/calib.cpp

HEADERS  += headers/mainwindow.h \
            headers/convert.h \
            headers/include.h \
            headers/edit.h \
            headers/calib.h

# The following lines tells Qmake to use pkg-config for opencv
QT_CONFIG -= no-pkg-config
CONFIG  += link_pkgconfig
PKGCONFIG += opencv

# Faire un cas pour les machines du Cremi.
# /opt/local/stow <- OpenCV là-dedans.
