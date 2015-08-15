#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
///
#include <qcustomplot.h>
///
#include <miniscanxe.h>
#include <spectralops.h>
#include <dlggrafica.h>
#include <dlgfototipo.h>

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

    void on_actionAcerca_de_triggered();

    void on_btnEstandarizar_clicked();

    void on_btnFototipo_clicked();

    void on_btnReflectancia_clicked();

    void on_btnAbsorbancia_clicked();

private:
    Ui::MainWindow *ui;
    MiniScanXE miniscan;
    SpectralOps ops;
    dlgGrafica *ref, *abs;
    QStandardItemModel *modelo;
    QList<QVariant> medicion;
    int numCurvas, yRef, yAbs;
    bool conectado;
    QString version;
};

#endif // MAINWINDOW_H
