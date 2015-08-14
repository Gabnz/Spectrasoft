#include "spectralops.h"

SpectralOps::SpectralOps()
{

}

float SpectralOps::eritema(QVector<double> medicion)
{
    /*promRojo: calcula el promedio ponderado del rango de longitud de onda que produce
        la sensacion de color rojo, dandole mayor importancia a los puntos que se encuentran en el medio*/
    float promRojo = (medicion[24]/2 + medicion[25] + medicion[26] + medicion[27]/2)/3;

    /*promVerde: calcula el promedio ponderado del rango de longitud de onda que produce
        la sensacion de color verde, dandole mayor importancia al punto que se encuentra en el medio*/
    float promVerde = (medicion[16]/2 + medicion[17] + medicion[18]/2)/2;

    /*E = calcula el indice de eritema, empleando el uso de los promedios calculados anteriormente*/
    float E = log(1/promVerde) - log(1/promRojo);

    return E;
}

int SpectralOps::fototipo()
{
    int resultado = rand() % 6 + 1;

    return resultado;
}

SpectralOps::~SpectralOps()
{

}

