#include "spectralops.h"

SpectralOps::SpectralOps()
{

}

QVector<float> SpectralOps::CIExyz(QVector<float> medicion)
{
    QVector<float> resultado;
    int i;
    float k, auxK, auxX, auxY, auxZ, X, Y, Z, x, y, z;

    auxK = 0;

    for(i = 0; i < 31; ++i){

        auxK+= (iluCIED65[i]*yCIE10[i]);
    }

    k = 100/auxK;

    auxX = auxY = auxZ = 0;

    for(i = 0; i < 31; ++i){

        auxX+= (medicion[i]*iluCIED65[i]*xCIE10[i]);
        auxY+= (medicion[i]*iluCIED65[i]*yCIE10[i]);
        auxY+= (medicion[i]*iluCIED65[i]*zCIE10[i]);
    }

    X = (k*auxX);
    Y = (k*auxY);
    Z = (k*auxZ);

    x = X/(X + Y + Z);
    y = Y/(X + Y + Z);
    z = Z/(X + Y + Z);

    resultado.push_back(x);
    resultado.push_back(y);
    resultado.push_back(z);

    return resultado;
}

QVector<float> SpectralOps::CIELAB(QVector<double> medicion)
{
    QVector<float> resultado;

    resultado.push_back(0);
    resultado.push_back(0);
    resultado.push_back(0);

    return resultado;
}

float SpectralOps::absorcion(QVector<double> medicion)
{
    float resultado;

    resultado = 0;

    return resultado;
}

float SpectralOps::esparcimiento(QVector<double> medicion)
{
    float resultado;

    resultado = 0;

    return resultado;
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
    float resultado = log(1/promVerde) - log(1/promRojo);

    return resultado;
}

int SpectralOps::fototipo()
{
    int resultado = rand() % 6 + 1;

    return resultado;
}

SpectralOps::~SpectralOps()
{

}

