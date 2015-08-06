#-------------------------------------------------
#
# Project created by QtCreator 2015-07-07T21:22:17
#
#-------------------------------------------------

QT       += core gui
QT += axcontainer
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Spectralsoft
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    spectralops.cpp \
    miniscanxe.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    spectralops.h \
    miniscanxe.h

FORMS    += mainwindow.ui
