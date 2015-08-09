#ifndef GRAFICA_H
#define GRAFICA_H

#include <QMainWindow>
#include <qcustomplot.h>

class Grafica
{
public:
    Grafica(QCustomPlot *graficaExt, QMainWindow *padreExt, QString tituloExt, QString etqX, QString etqY);
    void agregarCurva(QVector<double> y);
    void ajustarGrafica(QString axis, const QCPRange &newRange);
    ~Grafica();

private:
    QCustomPlot *grafica;
    QMainWindow *padre;
    QVector<double> x;
};

#endif // GRAFICA_H
