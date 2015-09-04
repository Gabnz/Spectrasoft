#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
///
#include <qcustomplot.h>
///
#include <miniscanxe.h>
#include <dlgestandarizar.h>
#include <spectralops.h>
#include <dlggrafica.h>
#include <dlgfototipo.h>
#include <dlgdatosadicionales.h>
#include <dlginiciosesion.h>
#include <dlgverusuario.h>
#include <dlgregusuario.h>
#include <dlgeliminarusuario.h>
#include <dlgreghistoria.h>
#include <dlgverhistoria.h>
#include <dlgbuscarhistoria.h>
#include <dlgeliminarhistoria.h>
#include <QtSql>

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

    void on_btnEliminar_clicked();

    void on_actionIniciar_sesion_triggered();

    void on_actionCerrar_sesion_triggered();

    void on_actionVer_usuario_triggered();

    void closeEvent(QCloseEvent *event);

    void on_actionCerrar_historia_triggered();

    void on_actionRegistrar_historia_triggered();

    void on_actionRegistrar_usuario_triggered();

    void on_actionEliminar_usuario_triggered();

    void on_actionVer_historia_triggered();

    void on_actionBuscar_historia_triggered();

    void on_actionEliminar_historia_triggered();

private:
    Ui::MainWindow *ui;
    MiniScanXE miniscan;
    SpectralOps ops;
    QSqlDatabase db;
    dlgGrafica *ref, *abs;
    dlgDatosAdicionales *dts;
    QVector<float> datosEspectrales;
    QStandardItemModel *modeloDatos;
    int numCurvas;
    bool conectado;
    QString version;
    QHash<QString, QString> infoUsuario, infoHistoria;
};

#endif // MAINWINDOW_H
