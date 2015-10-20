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


const int colum= 587;
const int fil=6;
const int A=3;
const int S=3;
const int N= colum+1;

class msv
{

public:
    msv();
    ~msv();
    /*Extrae los datos de un archivo xlsx (Excel)*/
    void ExtraccionDatos();
    void CargaDatos();
    void Discretizacion(double matrixD[colum][fil]);
    void sort(int n);
    void out();
    double inconsistency();
    double CAIM(int i,int n,double selectvalue,double point[N],double canpoint[N],int l);
    //double logaaa(int i,int n,double canpoint[N],int l);
    void findsort(int cai[N],double caivalue[N],int j,double caic);
    void replace(int i,double cutpoint[N],int ll);

    /*Entrenamiento*/
    void msv_train(QFile *Datos);
    /*Predicciones*/
    void msv_predict(QFile *Datos);
    void predict(QFile *input, QFile *output);
    void DefParametros();
    void read_problem(QFile *Datos);
    float do_cross_validation();
    void OptimizacionParametros();

    /*Imprime las Medidas de Evaluacion del Clasificador*/
    void Print_Medidas(int matrixConf[7][7],QVector<int> Inst_Correct, QVector<int> Inst_incorrc, int correct, int total, int a);

    /*Funcion administrador*/
    void Entrada(QVector<float> Datos);
    void Administrador();
    int UsuarioMedico();
    int Clasificacion(QFile *input);

    /*Resultado Para Uusuario Medico*/


};

#endif // MSV_H
