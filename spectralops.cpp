#include "spectralops.h"

SpectralOps::SpectralOps()
{

}

QVector<float> SpectralOps::absorbancia(QVector<float> medicion)
{
    QVector<float> resultado;

    for(int i = 0; i < 31; ++i){
        resultado.push_back(100.0 - medicion[i]);
    }

    return resultado;
}

QVector<float> SpectralOps::CIEXYZ(QVector<float> medicion)
{
    QVector<float> resultado;
    float auxK, auxX, auxY, auxZ, k, X, Y, Z;

    k = X = Y = Z = auxK = auxX = auxY = auxZ = 0.0;

    //realiza las sumatorias indicadas de las formulas
    for(int i = 0; i < 31; ++i){

        auxK+= iluCIED65[i]*yCIE10[i];
        auxX+= medicion[i]*iluCIED65[i]*xCIE10[i];
        auxY+= medicion[i]*iluCIED65[i]*yCIE10[i];
        auxZ+= medicion[i]*iluCIED65[i]*zCIE10[i];
    }

    //calcula la constante k
    k = 100.0/auxK;

    //calcula los valores triestimulo XYZ
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
    QVector<float> XYZ = CIEXYZ(medicion);
    float x, y, z;

    x = y = z = 0.0;

    //calcula las coordenadas tricromaticas xyz
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
    QVector<float> XYZ = CIEXYZ(medicion);
    float constante, aux, fXfYfZ[3], L, a, b;

    //calcula la constante utilizada en la formula
    constante = 24.0/116.0;
    constante = pow(constante, 3);

    //calcula las funciones X/Xn, Y/Yn, Z/Zn
    for(int i = 0; i < 3; ++i){

        aux = XYZ[i]/XnYnZn[i];

        if(aux > constante){
            fXfYfZ[i] = pow(aux, 1.0/3.0);
        }else{
            fXfYfZ[i] = (841.0/108.0)*aux + (16.0/116.0);
        }
    }

    //calcula las coordenadas L*a*b*
    L = 116.0*fXfYfZ[1] - 16.0;
    a = 500.0*(fXfYfZ[0] - fXfYfZ[1]);
    b = 200.0*(fXfYfZ[1] - fXfYfZ[2]);

    resultado.push_back(L);
    resultado.push_back(a);
    resultado.push_back(b);

    return resultado;
}

QVector<float> SpectralOps::absorcion(QVector<float> medicion)
{
    QVector<float> resultado;
    float rango, aux, Z, k, a0;
    int n, grado;
    bool op = false; //el sistema de ecuaciones a resolver tiene solucion

    //son 31 datos, y el grado del polinomio de ajuste es 8
    n = 31; grado = 8;

    double *x = new double[n];
    double *y = new double[n];

    //cargando los datos en x, y
    for(int i = 0; i < n; ++i){
        x[i] = i;
        y[i] = medicion.at(i);
    }

    double **matriz = new double*[grado + 1];

    for (int i = 0; i < grado + 1; ++i)
        matriz[i] = new double[grado + 2];

    //realizando el ajuste polinomial y calculando los coeficientes
    coeficientes(x, y, matriz, grado, n);
    recorrido(matriz, grado + 1, op);

    //a0 esta en la primera fila de la matriz resultante del ajuste
    a0 = matriz[0][grado + 1];
    Z = 0.2796; k = -7.174;
    rango = 400;

    //calculando el coeficiente de absorcion
    for(int i = 0; i < n; ++i){
        aux = Z*exp(k*a0)*6.6*pow(10, 11)*pow(rango, -3.3);
        resultado.push_back(aux);
        rango+=10;
    }

    //liberando la memoria dinamica asiganada
    delete x;
    delete y;

    for(int i = 0; i < grado + 1; ++i)
        delete matriz[i];

    delete matriz;

    return resultado;
}

float SpectralOps::eritema(QVector<float> medicion)
{
    /*promRojo: contiene el promedio ponderado del rango de longitud de onda que produce
        la sensacion de color rojo, dandole mayor importancia a los puntos que se encuentran en el medio*/
    float promRojo = (medicion[24]/2.0 + medicion[25] + medicion[26] + medicion[27]/2.0)/3.0;

    /*promVerde: contiene el promedio ponderado del rango de longitud de onda que produce
        la sensacion de color verde, dandole mayor importancia al punto que se encuentra en el medio*/
    float promVerde = (medicion[16]/2.0 + medicion[17] + medicion[18]/2.0)/2.0;

    /*resultado = contiene el indice de eritema, empleando el uso de los promedios calculados anteriormente*/
    float resultado = 100.0*(log(1.0/promVerde) - log(1.0/promRojo));

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

