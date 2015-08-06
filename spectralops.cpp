#include "spectralops.h"

SpectralOps::SpectralOps()
{

}

float SpectralOps::eritema(QList<QVariant> medicion)
{
    /*promRojo: calcula el promedio ponderado del rango de longitud de onda que produce
        la sensacion de color rojo, dandole mayor importancia a los puntos que se encuentran en el medio*/
    float promRojo = (medicion.at(24).toFloat()/2 + medicion.at(25).toFloat() + medicion.at(26).toFloat() + medicion.at(27).toFloat()/2)/3;

    /*promVerde: calcula el promedio ponderado del rango de longitud de onda que produce
        la sensacion de color verde, dandole mayor importancia al punto que se encuentra en el medio*/
    float promVerde = (medicion.at(16).toFloat()/2 + medicion.at(17).toFloat() + medicion.at(18).toFloat()/2)/2;

    /*E = calcula el indice de eritema, empleando el uso de los promedios calculados anteriormente*/
    float E = log10(1/promVerde) - log10(1/promRojo);

    return E;
}

SpectralOps::~SpectralOps()
{

}

