#ifndef GRAFICA_H
#define GRAFICA_H

#include <QMainWindow>
#include <qcustomplot.h>

class Grafica
{
public:
    Grafica(QCustomPlot *graficaExt, QMainWindow *padreExt, QString tituloExt, QString etqX, QString etqY);
    void agregarCurva(QVector<double> y);
    bool numCurvas();
    void quitarCurva();
    void ajustarGrafica(QString axis, const QCPRange &newRange, double lower,double upper);
    ~Grafica();

private:
    QCustomPlot *grafica;
    QMainWindow *padre;
    QVector<double> x;
    int n;
};

#endif // GRAFICA_H
