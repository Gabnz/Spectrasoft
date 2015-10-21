#include "objmsv.h"

objMsv::objMsv(QObject *parent) : QObject(parent)
{

}

void objMsv::start(QVector<float> LAB)
{
    msv aux;

    aux.ExtraccionDatos();
    aux.Entrada(LAB);
    int resultado = aux.UsuarioMedico();

    emit fototipo_recomendado(resultado);
}

objMsv::~objMsv()
{

}

