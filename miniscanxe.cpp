#include "miniscanxe.h"

MiniScanXE::MiniScanXE()
{
    //Busca y asigna el control definido para MSXE.bridge
    miniscan.setControl("MSXE.Bridge");

    conectado = negroEstandarizado = blancoEstandarizado = false;
    puertoCOM = 0;
}

bool MiniScanXE::conectar()
{
    QList<QSerialPortInfo> puertos = QSerialPortInfo::availablePorts();

    //prueba abrir cada uno de los puertos COM disponibles en el momento
    while(!conectado && puertos.size() > 0){

        QSerialPortInfo puerto = puertos.at(0);
        puertos.removeAt(0);
        puertoCOM = puerto.portName().remove("COM").toInt();
        conectado = miniscan.dynamicCall("abrirPuerto(int)", puertoCOM).toBool();
    }

    if(conectado){
        miniscan.dynamicCall("BeepDoble()");
    }

    return conectado;
}

bool MiniScanXE::desconectar()
{
    conectado = !(miniscan.dynamicCall("cerrarPuerto()").toBool());

    return conectado;
}

bool MiniScanXE::estNegro()
{
    negroEstandarizado = miniscan.dynamicCall("leerNegro()").toBool();

    return negroEstandarizado;
}

bool MiniScanXE::estBlanco()
{
    blancoEstandarizado = miniscan.dynamicCall("leerBlanco()").toBool();

    return blancoEstandarizado;
}

QList<QVariant> MiniScanXE::medir()
{
    QVariant resultado;
    QList<QVariant> medicion;

    //realiza una medicion y la almacena
    resultado = miniscan.dynamicCall("medirMuestra()");
    medicion = resultado.toList();

    QList<QVariant>::const_iterator iter = qFind(medicion.begin(), medicion.end(), 0);

    if(iter == medicion.end()){
        //si no se consigue ningun cero exacto (0), es porque la lista fue llenada correctamente y por lo tanto la medicion ocurrio
        miniscan.dynamicCall("Beep()");
    }

    return medicion;
}

MiniScanXE::~MiniScanXE()
{

}

