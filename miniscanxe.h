#ifndef MINISCANXE_H
#define MINISCANXE_H

#include <QAxObject>
#include <QAxBase>
#include <QAxWidget>
#include <QtSerialPort>
#include <QDebug>

class MiniScanXE
{
public:
    MiniScanXE();
    bool conectar();
    bool desconectar();
    bool estNegro();
    bool estBlanco();
    QList<QVariant> medir();
    ~MiniScanXE();

private:
    QAxObject miniscan;
    int puertoCOM;
    bool conectado, negroEstandarizado, blancoEstandarizado;
};

#endif // MINISCANXE_H
