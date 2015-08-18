#include "spectralops.h"

SpectralOps::SpectralOps()
{

}

QVector<float> SpectralOps::CIEXYZ(QVector<float> medicion)
{
    QVector<float> resultado;
    float auxK, auxX, auxY, auxZ, k, X, Y, Z;

    auxK = auxX = auxY = auxZ = 0.0;

    for(int i = 0; i < 31; ++i){

        auxK+= iluCIED65[i]*yCIE10[i];
        auxX+= medicion[i]*iluCIED65[i]*xCIE10[i];
        auxY+= medicion[i]*iluCIED65[i]*yCIE10[i];
        auxY+= medicion[i]*iluCIED65[i]*zCIE10[i];
    }

    k = 100.0/auxK;

    X = k*auxX;
    Y = k*auxY;
    Z = k*auxZ;

    resultado.push_back(X);
    resultado.push_back(Y);
    resultado.push_back(Z);

    return resultado;
}

QVector<float> SpectralOps::CIExyz(QVector<float> medicion)
{
    QVector<float> resultado;
    float x, y, z;
    QVector<float> XYZ = CIEXYZ(medicion);

    x = XYZ[0]/(XYZ[0] + XYZ[1] + XYZ[2]);
    y = XYZ[1]/(XYZ[0] + XYZ[1] + XYZ[2]);
    z = XYZ[2]/(XYZ[0] + XYZ[1] + XYZ[2]);

    resultado.push_back(x);
    resultado.push_back(y);
    resultado.push_back(z);

    return resultado;
}

QVector<float> SpectralOps::CIELAB(QVector<float> medicion)
{
    QVector<float> resultado;
    float constante, aux, fXfYfZ[3], L, a, b;

    constante = 24.0/116.0;
    constante = pow(constante, 3);

    QVector<float> XYZ = CIEXYZ(medicion);

    for(int i = 0; i < 3; ++i){

        aux = XYZ[i]/XnYnZn[i];

        if(aux > constante){
            fXfYfZ[i] = pow(aux, 1.0/3.0);
        }else{
            fXfYfZ[i] = (841.0/108.0)*aux + (16.0/116.0);
        }
    }

    L = 116.0*fXfYfZ[1] - 16.0;
    a = 500.0*(fXfYfZ[0] - fXfYfZ[1]);
    b = 200.0*(fXfYfZ[1] - fXfYfZ[2]);

    resultado.push_back(L);
    resultado.push_back(a);
    resultado.push_back(b);

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
    float promRojo = (medicion[24]/2.0 + medicion[25] + medicion[26] + medicion[27]/2.0)/3.0;

    /*promVerde: calcula el promedio ponderado del rango de longitud de onda que produce
        la sensacion de color verde, dandole mayor importancia al punto que se encuentra en el medio*/
    float promVerde = (medicion[16]/2.0 + medicion[17] + medicion[18]/2.0)/2.0;

    /*E = calcula el indice de eritema, empleando el uso de los promedios calculados anteriormente*/
    float resultado = log(1.0/promVerde) - log(1.0/promRojo);

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

