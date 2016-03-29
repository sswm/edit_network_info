#-------------------------------------------------
#
# Project created by QtCreator 2016-03-29T14:12:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = edit_network_info
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    weather.cpp

HEADERS  += mainwindow.h \
    weather.h

FORMS    += mainwindow.ui \
    weather.ui
