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
    void borrarResultados();
    void revisionBtns();
    ~MainWindow();

private slots:
    void on_actionConectar_triggered();

    void on_actionDesconectar_triggered();

    void on_actionSalir_triggered();

    void on_btnMedir_clicked();

    void on_actionAcerca_de_triggered();

    void on_btnFototipo_clicked();

    void on_btnReflectancia_clicked();

    void on_btnAbsorbancia_clicked();

    void on_actionEstandarizar_triggered();

    void on_btnBorrar_clicked();

private:
    Ui::MainWindow *ui;
    MiniScanXE miniscan;
    SpectralOps ops;
    dlgGrafica *ref, *abs;
    QStandardItemModel *modeloPuntos, *modeloXYZ, *modeloLAB, *modeloAbsEsp;
    QList<QVariant> medicion;
    int numCurvas, yRef, yAbs, fototipo;
    bool conectado;
    QString version;
};

#endif // MAINWINDOW_H
