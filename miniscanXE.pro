#-------------------------------------------------
#
# Project created by QtCreator 2015-07-07T21:22:17
#
#-------------------------------------------------

QT       += core gui
QT += axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = miniscanXE
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h

FORMS    += mainwindow.ui
