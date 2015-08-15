#ifndef SPECTRALOPS_H
#define SPECTRALOPS_H

#include <QVector>
#include <math.h>

class SpectralOps
{
public:
    SpectralOps();

    QVector<float> CIEXYZ(QVector<double> medicion);
    QVector<float> CIELAB(QVector<double> medicion);
    float absorcion(QVector<double> medicion);
    float esparcimiento(QVector<double> medicion);
    /*
        Retorna el indice de eritema, utilizado para determinar el nivel
        inflamatorio de la epidermis en la piel de un paciente.

        @param medicion la lista que contiene los 31 puntos espectrales de la muestra
        @return el indice de eritema.
    */
    float eritema(QVector<double> medicion);

    /*
        Retorna el fototipo de la piel de un paciente segun la escala Fitz Patrick, empleando
        el uso de un algoritmo en vias de desarrollo.

        @return el fototipo.
    */
    int fototipo();
    ~SpectralOps();
};

#endif // SPECTRALOPS_H
