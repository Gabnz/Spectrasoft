#ifndef MSV_H
#define MSV_H

#include <clasificador/svm.h>
#include <iostream>
#include <QFile>
#include <QVector>
#include <iostream>
#include <QString>
#include <QTextStream>
#include <QtAlgorithms>
#include <QDebug>
#include <QDir>
#include <QByteArray>
#include <QIODevice>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <xlsxdocument.h>
#include <QStandardPaths>


/*Cantidad total de
Muestras de fototipos*/
const int colum= 587;

/* A = Representa la
 * Cantidad de Atributos,
    *L, *a, *b
*/
const int A=3;

/* fil, N, S
 * Para construir
 * la QuantaMatrix
*/
const int N= colum+1;
const int fil=6;
const int S=3;

class msv
{
    svm_problem prob;
    svm_parameter parametro;
    svm_model *model;
    svm_node *x_space;
    svm_node *x;

    QString url;
    std::string str;
    /*nr_fold para validacion cruzada (Cross-validation)*/
    int nr_fold;

    char model_file_name[1024];
    int max_nr_attr;
    int predict_probability;

    /*dataD almacena la QuantaMatrix para la discretizacion*/
    float dataD[colum+1][fil];

    /*Numero de Columnas y Filas del archivo Excel*/
    int nColum;
    int nFilas;

public:

    msv();
    ~msv();
    /*Extrae los datos de un archivo xlsx (Excel)*/
    void ExtraccionDatos();
    void Entrada(QVector<float> Datos);

    /*Inicia Proceso de Discretizacion*/
    void Discretizacion(float matrixD[colum][fil]);

    /*Ordena el vector de intervalos*/
    void Ordenamiento(int n);

    float inconsistency();

    /*Obtiene la QuantaMatrix y Calcula el Valor CAIM*/
    float ValorCAIM(int i, int n, float selectvalue, float point[N]);
    void findsort(int cai[N],float caivalue[N],int j,float caic);
    void reemplazar(int i,float cutpoint[N],int ll);

    /*Almacena los valores dizcretizados en un archivo*/
    void out();
    /***********************************/

    /*Definicion de Parametros para el Kernel RFF*/
    void DefParametros();

    /*Entrenamiento, Recibe el conjunto de datos Discretizados*/
    void msv_train(QFile *Datos);

    /*Genera y almacena el Modelo*/
    void msv_predict(QFile *Datos);

    /*Evalua el modelo generado*/
    void predict(QFile *input, QFile *output);

    void read_problem(QFile *Datos);

    /*Ejecuta el proceso de Validacion Cruzada con 98 fold*/
    float do_cross_validation();

    /*Optimiza los parametros del kernel RBF (gamma y C)*/
    void OptimizacionParametros();

    /*Imprime las Medidas de Evaluacion del Clasificador*/
    void Print_Medidas(int matrixConf[7][7],QVector<int> Inst_Correct, QVector<int> Inst_incorrc, int correct, int total, int a);

    /*Administrados para reentrenar el clasificador*/
    void Administrador();

    /*Funcion UsuarioMedico Carga el Modelo alamacenado y
     * retorna el fototipo de una nueva muestra*/
    int UsuarioMedico();

    /*Funcion Clasificacion recibe los valores *L, *a, *b del fototipo
     * y retorna el fototipo clasificado*/
    int Clasificacion(QFile *input);

};

#endif // MSV_H
