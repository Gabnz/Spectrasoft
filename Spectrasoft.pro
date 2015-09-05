#-------------------------------------------------
#
# Project created by QtCreator 2015-07-07T21:22:17
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT += axcontainer
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Spectrasoft
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    spectralops.cpp \
    miniscanxe.cpp \
    dlgfototipo.cpp \
    dlggrafica.cpp \
    dlgdatosadicionales.cpp \
    dlgestandarizar.cpp \
    dlginiciosesion.cpp \
    dlgverusuario.cpp \
    dlgreghistoria.cpp \
    dlgregusuario.cpp \
    dlgeliminarusuario.cpp \
    dlgverhistoria.cpp \
    dlgbuscarhistoria.cpp \
    dlgeliminarhistoria.cpp \
    dlgconfirmarclave.cpp \
    dlgmodificarhistoria.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    spectralops.h \
    miniscanxe.h \
    dlgfototipo.h \
    dlggrafica.h \
    dlgdatosadicionales.h \
    dlgestandarizar.h \
    dlginiciosesion.h \
    dlgverusuario.h \
    dlgreghistoria.h \
    dlgregusuario.h \
    dlgeliminarusuario.h \
    dlgverhistoria.h \
    dlgbuscarhistoria.h \
    dlgeliminarhistoria.h \
    dlgconfirmarclave.h \
    dlgmodificarhistoria.h

FORMS    += mainwindow.ui \
    dlgfototipo.ui \
    dlggrafica.ui \
    dlgdatosadicionales.ui \
    dlgestandarizar.ui \
    dlginiciosesion.ui \
    dlgverusuario.ui \
    dlgreghistoria.ui \
    dlgregusuario.ui \
    dlgeliminarusuario.ui \
    dlgverhistoria.ui \
    dlgbuscarhistoria.ui \
    dlgeliminarhistoria.ui \
    dlgconfirmarclave.ui \
    dlgmodificarhistoria.ui

RESOURCES += \
    recursos.qrc

RC_ICONS += img/logo_icono.ico
