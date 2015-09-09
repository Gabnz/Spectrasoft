#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <qcustomplot.h>
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
#include <dlgmodificarhistoria.h>
#include <dlgeliminarhistoria.h>
#include <dlgtipomuestra.h>
#include <dlgreglesion.h>
#include <dlgverlesion.h>
#include <dlgregfototipo.h>
#include <dlgmodificarlesion.h>
#include <dlgeliminarmuestra.h>
#include <dlgacercade.h>

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

    void on_actionSalir_triggered();

    void on_actionAcerca_de_triggered();

    void on_actionEstandarizar_triggered();

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

    void on_historiaEliminada();

    void on_actionModificar_historia_triggered();

    void on_historiaModificada(QHash<QString, QString> infoModificada);

    void on_actionMedir_muestra_triggered();

    void on_actionEliminar_muestra_triggered();

    void on_muestraEliminada();

    void on_actionVer_reflectancia_triggered();

    void on_actionVer_absorbancia_triggered();

    void on_actionDatos_adicionales_triggered();

    void on_actionBorrar_resultados_triggered();

    void on_actionRegistrar_muestra_triggered();

    void on_tipoMuestra(const QString tipo);

    void on_muestraRegistrada(const QHash<QString, QString> info);

    void on_actionVer_muestra_triggered();

    void on_actionCerrar_muestra_triggered();

    void on_actionModificar_muestra_triggered();

    void on_muestraModificada(QHash<QString, QString> infoModificada);

private:
    Ui::MainWindow *ui;
    MiniScanXE miniscan;
    SpectralOps ops;
    QSqlDatabase db;
    dlgGrafica *ref, *abs;
    dlgDatosAdicionales *dts;
    QVector<float> datosEspectrales, XYZ, LAB;
    float absorcion, esparcimiento, eritema;
    QStandardItemModel *modeloDatos;
    int numCurvas;
    bool conectado;
    QHash<QString, QString> infoUsuario, infoHistoria, infoMuestra;
};

#endif // MAINWINDOW_H
