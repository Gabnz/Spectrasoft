#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
///
#include <qcustomplot.h>
#include <limits>
///
#include <miniscanxe.h>
#include <spectralops.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void revisionBtns();
    ~MainWindow();

private slots:
    void on_actionConectar_triggered();

    void on_actionDesconectar_triggered();

    void on_actionSalir_triggered();

    void on_btnMedir_clicked();

    void ajustarRefX(const QCPRange &newRange);

    void ajustarRefY(const QCPRange &newRange);

    void ajustarAbsX(const QCPRange &newRange);

    void ajustarAbsY(const QCPRange &newRange);

    void on_actionEstandarizar_Negro_triggered();

    void on_actionEstandarizar_Blanco_triggered();

    void on_refSpinY_valueChanged(double arg1);

    void on_absSpinY_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    MiniScanXE miniscan;
    SpectralOps ops;
    int yRefMax, yAbsMax, numCurvas;
    QVector<double> x;
    bool conectado;
};

#endif // MAINWINDOW_H
