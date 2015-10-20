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
#include <dlgmodificarusuario.h>
#include <dlgcambiarclave.h>
#include <dlgregusuario.h>
#include <dlgadministrarusuarios.h>
#include <dlgeliminarusuario.h>
#include <dlgreghistoria.h>
#include <dlgverhistoria.h>
#include <dlgbuscarhistoria.h>
#include <dlgmodificarhistoria.h>
#include <dlgeliminarhistoria.h>
#include <dlgtipomuestra.h>
#include <dlgreglesion.h>
#include <dlgregfototipo.h>
#include <dlgbuscarmuestra.h>
#include <dlgvermuestra.h>
#include <xlsxdocument.h>
#include <dlgmodificarmuestra.h>
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

    /*
     * Habilita o deshabilita los botones y acciones disponibles en la interfaz, dependiendo del caso.
     */
    void revisionBtns();

    /*
     * Borra los resultados de una medicion realizada.
     */
    void borrarResultados();

    ~MainWindow();

private slots:
    /*
     * Operaciones básicas de gestión del MiniScan, gestión de las mediciones y del software.
     */
    void on_actionConectar_triggered();

    void on_actionEstandarizar_triggered();

    void on_actionRealizar_medicion_triggered();

    void on_actionVer_reflectancia_triggered();

    void on_actionVer_absorbancia_triggered();

    void on_actionVer_absorcion_triggered();

    void on_actionDatos_adicionales_triggered();

    void on_actionBorrar_resultados_triggered();

    void on_actionSalir_triggered();

    void closeEvent(QCloseEvent *event);

    void on_actionAcerca_de_triggered();

    /*
     * Operaciones de gestión de usuario.
     */
    void on_actionIniciar_sesion_triggered();

    void on_sesionIniciada(QHash<QString, QString> info);

    void on_actionVer_usuario_triggered();

    void on_actionModificar_usuario_triggered();

    void on_usuarioModificado(QHash<QString, QString> infoModificada);

    void on_claveCambiada(QString info);

    void on_actionRegistrar_usuario_triggered();

    void on_actionAdministrar_usuarios_triggered();

    void on_actionCambiar_clave_triggered();

    void on_actionCerrar_sesion_triggered();

    /*
     * Operaciones de gestión de historia.
     */
    void on_actionRegistrar_historia_triggered();

    void on_historiaRegistrada(QHash<QString, QString> info);

    void on_actionVer_historia_triggered();

    void on_actionBuscar_historia_triggered();

    void on_historiaAbierta(QHash<QString, QString> info);

    void on_actionModificar_historia_triggered();

    void on_historiaModificada(QHash<QString, QString> infoModificada);

    void on_actionEliminar_historia_triggered();

    void on_historiaEliminada();

    void on_actionCerrar_historia_triggered();

    /*
     * Operaciones de gestión de muestra.
     */
    void on_tipoMuestra(const QString tipo);

    void on_actionRegistrar_muestra_triggered();

    void on_muestraRegistrada(const QHash<QString, QString> info);

    void on_actualizarFototipo(int infoF);

    void on_actionBuscar_muestra_triggered();

    void on_muestraAbierta(QHash<QString, QString> infoM, float infoDatos[2][31], float infoCoordenadas[2][3], float infoEritema);

    void on_actionVer_muestra_triggered();

    void on_actionModificar_muestra_triggered();

    void on_muestraModificada(QHash<QString, QString> infoModificada);

    void on_actionExportar_muestra_triggered();

    void on_actionEliminar_muestra_triggered();

    void on_muestraEliminada();

    void on_actionCerrar_muestra_triggered();

private:
    Ui::MainWindow *ui;
    MiniScanXE miniscan;
    SpectralOps ops;
    QSqlDatabase db;
    dlgGrafica *ref, *abs, *absorcion;
    dlgDatosAdicionales *dts;
    QVector<float> datosEspectrales, datosAbsorbancia, XYZ, LAB, datosAbsorcion;
    float eritema;
    QStandardItemModel *modeloDatos;
    bool conectado, bdConectada;
    QHash<QString, QString> infoUsuario, infoHistoria, infoMuestra;
};

#endif // MAINWINDOW_H
