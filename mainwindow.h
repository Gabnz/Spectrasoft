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
#include <dlgdatosadicionales.h>

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

//    void on_btnFototipo_clicked();

    void on_btnReflectancia_clicked();

    void on_btnDatosAdicionales_clicked();

    void on_btnAbsorbancia_clicked();

    void on_actionEstandarizar_triggered();

    void on_btnBorrar_clicked();

private:
    Ui::MainWindow *ui;
    MiniScanXE miniscan;
    SpectralOps ops;
    dlgGrafica *ref, *abs;
    dlgDatosAdicionales *dts;
    QVector<float> datosEspectrales;
    QStandardItemModel *modeloPuntos;
    int numCurvas;
    bool conectado;
    QString version;
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
