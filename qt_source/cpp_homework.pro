#-------------------------------------------------
#
# Project created by QtCreator 2016-06-01T11:40:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cpp_homework
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog_call.cpp \
    dialog_read.cpp

HEADERS  += mainwindow.h \
    dialog_call.h \
    dialog_read.h

FORMS    += mainwindow.ui \
    dialog_call.ui \
    dialog_read.ui
