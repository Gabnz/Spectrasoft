#ifndef DLGGRAFICA_H
#define DLGGRAFICA_H

#include <QDialog>
#include <qcustomplot.h>

namespace Ui {
class dlgGrafica;
}

class dlgGrafica : public QDialog
{
    Q_OBJECT

public:
    explicit dlgGrafica(QString tituloExt, QString etqX, QString etqY, int yMaxExt, QWidget *parent = 0);
    void agregarCurva(QVector<double> y);
    bool numCurvas();
    void quitarCurva();
    void ajustarGrafica(QString axis, const QCPRange &newRange, double lower,double upper);
    ~dlgGrafica();

private slots:
    void ajustarX(const QCPRange &newRange);

    void ajustarY(const QCPRange &newRange);

    void on_spinY_valueChanged(double arg1);

private:
    Ui::dlgGrafica *ui;
    QVector<double> x;
    int n, yMax;
};

#endif // DLGGRAFICA_H
