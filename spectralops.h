#ifndef SPECTRALOPS_H
#define SPECTRALOPS_H

#include <QVector>
#include <QDebug>
#include <math.h>

/*Distribucion de energia espectral relativa del iluminante estandar CIE D65*/
const float iluCIED65[31] = {
/*400nm*/82.7549,
/*410nm*/91.4860,
/*420nm*/93.4318,
/*430nm*/86.6823,
/*440nm*/104.865,
/*450nm*/117.008,
/*460nm*/117.812,
/*470nm*/114.861,
/*480nm*/115.923,
/*490nm*/108.811,
/*500nm*/109.354,
/*510nm*/107.802,
/*520nm*/104.790,
/*530nm*/107.689,
/*540nm*/104.405,
/*550nm*/104.046,
/*560nm*/100.000,
/*570nm*/96.3342,
/*580nm*/95.7880,
/*590nm*/88.6856,
/*600nm*/90.0062,
/*610nm*/89.5991,
/*620nm*/87.6987,
/*630nm*/83.2886,
/*640nm*/83.6992,
/*650nm*/80.0268,
/*660nm*/80.2146,
/*670nm*/82.2778,
/*680nm*/78.2842,
/*690nm*/69.7213,
/*700nm*/71.6091};

/*Funciones de correspondencia del color, dado el observador estandar CIE de 10 grados*/
const float xCIE10[31] = {
/*400nm*/0.019110,
/*410nm*/0.084736,
/*420nm*/0.204492,
/*430nm*/0.314679,
/*440nm*/0.383734,
/*450nm*/0.370702,
/*460nm*/0.302273,
/*470nm*/0.195618,
/*480nm*/0.080507,
/*490nm*/0.016172,
/*500nm*/0.003816,
/*510nm*/0.037465,
/*520nm*/0.117749,
/*530nm*/0.236491,
/*540nm*/0.376772,
/*550nm*/0.529826,
/*560nm*/0.705224,
/*570nm*/0.878655,
/*580nm*/1.014160,
/*590nm*/1.118520,
/*600nm*/1.123990,
/*610nm*/1.030480,
/*620nm*/0.856297,
/*630nm*/0.647467,
/*640nm*/0.431567,
/*650nm*/0.268329,
/*660nm*/0.152568,
/*670nm*/0.081261,
/*680nm*/0.040851,
/*690nm*/0.019941,
/*700nm*/0.009577};

const float yCIE10[31] = {
/*400nm*/0.002004,
/*410nm*/0.008756,
/*420nm*/0.021391,
/*430nm*/0.038676,
/*440nm*/0.062077,
/*450nm*/0.089456,
/*460nm*/0.128201,
/*470nm*/0.185190,
/*480nm*/0.253589,
/*490nm*/0.339133,
/*500nm*/0.460777,
/*510nm*/0.606741,
/*520nm*/0.761757,
/*530nm*/0.875211,
/*540nm*/0.961988,
/*550nm*/0.991761,
/*560nm*/0.997340,
/*570nm*/0.955552,
/*580nm*/0.868934,
/*590nm*/0.777405,
/*600nm*/0.658341,
/*610nm*/0.527963,
/*620nm*/0.398057,
/*630nm*/0.283493,
/*640nm*/0.179828,
/*650nm*/0.107633,
/*660nm*/0.060281,
/*670nm*/0.031800,
/*680nm*/0.015905,
/*690nm*/0.007749,
/*700nm*/0.003718};

const float zCIE10[31] = {
/*400nm*/0.086011,
/*410nm*/0.389366,
/*420nm*/0.972542,
/*430nm*/1.553480,
/*440nm*/1.967280,
/*450nm*/1.994800,
/*460nm*/1.745370,
/*470nm*/1.317560,
/*480nm*/0.772125,
/*490nm*/0.415254,
/*500nm*/0.218502,
/*510nm*/0.112044,
/*520nm*/0.060709,
/*530nm*/0.030451,
/*540nm*/0.013676,
/*550nm*/0.003988,
/*560nm*/0.000000,
/*570nm*/0.000000,
/*580nm*/0.000000,
/*590nm*/0.000000,
/*600nm*/0.000000,
/*610nm*/0.000000,
/*620nm*/0.000000,
/*630nm*/0.000000,
/*640nm*/0.000000,
/*650nm*/0.000000,
/*660nm*/0.000000,
/*670nm*/0.000000,
/*680nm*/0.000000,
/*690nm*/0.000000,
/*700nm*/0.000000};

/*Valores triestimulo del iluminante estandar CIE D65, tomando en cuenta el observador estandar CIE de 10 grados*/
const float XnYnZn[3] = {
/*Xn*/94.81,
/*Yn*/100.00,
/*Zn*/107.32
};

class SpectralOps
{
public:
    SpectralOps();

    /*
    **   Calcula los valores triestimulo CIE XYZ, dados los 31 datos espectrales de una muestra.
    **
    **  @param medicion         Vector que contiene los 31 datos espectrales de la muestra.
    **  @return QVector<float>  Valores triestimulo CIE XYZ.
    */
    QVector<float> CIEXYZ(QVector<float> medicion);

    /*
    **  Calcula las coordenadas de cromaticidad CIE xyz, dados los 31 datos espectrales de una muestra.
    **
    **  @param medicion         Vector que contiene los 31 datos espectrales de la muestra.
    **  @return QVector<float>  Coordenadas de cromaticidad CIE xyz.
    */
    QVector<float> CIExyz(QVector<float> medicion);

    /*
    **  Calcula las coordenadas de del espacio CIELAB, dados los 31 datos espectrales de una muestra.
    **
    **  @param medicion         Vector que contiene los 31 datos espectrales de la muestra.
    **  @return QVector<float>  Coordenadas del espacio CIELAB.
    */
    QVector<float> CIELAB(QVector<float> medicion);

    float absorcion(QVector<float> medicion);

    float esparcimiento(QVector<float> medicion);

    /*
    **  Calcula el indice de eritema asociado a los 31 datos espectrales de una muestra.
    **
    **  @param medicion         Vector que contiene los 31 datos espectrales de la muestra.
    **  @return float           Indice de eritema.
    */
    float eritema(QVector<float> medicion);

    /*
    **  Determina el fototipo de la piel de un paciente segun la escala Fitz Patrick, empleando
    **  el uso de un algoritmo en vias de desarrollo.
    **
    **  @return int             Fototipo cutaneo.
    */
    int fototipo();

    ~SpectralOps();

private:

};

#endif // SPECTRALOPS_H
