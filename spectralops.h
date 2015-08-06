#ifndef SPECTRALOPS_H
#define SPECTRALOPS_H

#include <QList>
#include <QVariant>
#include <math.h>

class SpectralOps
{
public:
    SpectralOps();

    /*
        Retorna el indice de eritema, utilizado para determinar el nivel
        inflamatorio de la epidermis en la piel de un paciente.

        @param medicion la lista que contiene los 31 puntos espectrales de la muestra
        @return el indice de eritema.
    */
    float eritema(QList<QVariant> medicion);
    ~SpectralOps();

private:
    QList<QVariant> medicion;
};

#endif // SPECTRALOPS_H
