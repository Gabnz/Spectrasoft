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
    dlgmodificarhistoria.cpp \
    dlgacercade.cpp \
    dlgtipomuestra.cpp \
    dlgreglesion.cpp \
    dlgregfototipo.cpp \
    dlgeliminarmuestra.cpp \
    dlgvermuestra.cpp \
    dlgmodificarmuestra.cpp \
    dlgbuscarmuestra.cpp \
    dlgmodificarusuario.cpp \
    dlgadministrarusuarios.cpp \
    dlgcambiarclave.cpp \
    dlgcambiarrol.cpp

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
    dlgmodificarhistoria.h \
    dlgacercade.h \
    dlgtipomuestra.h \
    dlgreglesion.h \
    dlgregfototipo.h \
    dlgeliminarmuestra.h \
    dlgvermuestra.h \
    dlgmodificarmuestra.h \
    dlgbuscarmuestra.h \
    dlgmodificarusuario.h \
    dlgadministrarusuarios.h \
    dlgcambiarclave.h \
    dlgcambiarrol.h

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
    dlgmodificarhistoria.ui \
    dlgacercade.ui \
    dlgtipomuestra.ui \
    dlgreglesion.ui \
    dlgregfototipo.ui \
    dlgeliminarmuestra.ui \
    dlgvermuestra.ui \
    dlgmodificarmuestra.ui \
    dlgbuscarmuestra.ui \
    dlgmodificarusuario.ui \
    dlgadministrarusuarios.ui \
    dlgcambiarclave.ui \
    dlgcambiarrol.ui

RESOURCES += \
    recursos.qrc

RC_ICONS += img/logo_icono_nuevo.ico

include(qtxlsx/src/xlsx/qtxlsx.pri)
