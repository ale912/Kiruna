#-------------------------------------------------
#
# Project created by QtCreator 2015-09-20T12:44:13
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kiruna
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    downloader.cpp

HEADERS  += widget.h \
    downloader.h

FORMS    += widget.ui
