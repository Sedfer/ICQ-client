#-------------------------------------------------
#
# Project created by QtCreator 2016-06-10T18:50:57
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICQ-client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    room.cpp \
    dialogwindow.cpp \
    logindialog.cpp

HEADERS  += mainwindow.h \
    room.h \
    dialogwindow.h \
    logindialog.h
