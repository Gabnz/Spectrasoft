#ifndef DLGREGFOTOTIPO_H
#define DLGREGFOTOTIPO_H

#include <QDialog>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <dlgfototipo.h>
#include <dlgconfirmarclave.h>

namespace Ui {
class dlgRegFototipo;
}

class dlgRegFototipo : public QDialog
{
    Q_OBJECT

public:
    explicit dlgRegFototipo(QString claveUsuario, QString usuario, QString historia, QVector<float> datosEspectralesExt, QVector<float> XYZExt, QVector<float> LABExt, QVector<float> absorcionExt, float eritemaExt, QWidget *parent = 0);
    bool camposListos();
    ~dlgRegFototipo();

signals:
    void fototipo_registrado(QHash<QString, QString> info);
    void actualizar_fototipo(int infoF);

private slots:
    void on_btnCancelar_clicked();

    void on_lineaArea_textChanged(const QString &arg1);

    void on_btnFototipo_clicked();

    void on_resetearFototipo();

    void on_fototipo(int numero);

    void on_btnRegistrar_clicked();

    void on_claveIntroducida(bool correcta);

private:
    Ui::dlgRegFototipo *ui;
    QString id_usuario, id_historia, id_muestra, id_datos_espectrales, clave;
    QVector<float> datosEspectrales, XYZ, LAB, datosAbsorcion;
    float eritema;
    QHash<QString, QString> infoMuestra;
    int fototipo;
};

#endif // DLGREGFOTOTIPO_H
