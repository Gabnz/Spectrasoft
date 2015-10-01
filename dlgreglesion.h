#ifndef DLGREGLESION_H
#define DLGREGLESION_H

#include <QDialog>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <dlgconfirmarclave.h>

namespace Ui {
class dlgRegLesion;
}

class dlgRegLesion : public QDialog
{
    Q_OBJECT

public:
    explicit dlgRegLesion(QString claveUsuario, QString usuario, QString historia, QVector<float> datosEspectralesExt, QVector<float> XYZExt, QVector<float> LABExt, QVector<float> absorcionExt, QVector<float> esparcimientoExt, float eritemaExt, QWidget *parent = 0);
    bool camposListos();
    ~dlgRegLesion();

signals:
    void lesion_registrada(QHash<QString, QString> info);

private slots:
    void on_btnCancelar_clicked();

    void on_lineaNombre_textChanged(const QString &arg1);

    void on_lineaArea_textChanged(const QString &arg1);

    void on_btnRegistrar_clicked();

    void on_claveIntroducida(bool correcta);

private:
    Ui::dlgRegLesion *ui;
    QString id_usuario, id_historia, id_muestra, id_datos_espectrales, clave;
    QVector<float> datosEspectrales, XYZ, LAB, datosAbsorcion, datosEsparcimiento;
    float eritema;
    QHash<QString, QString> infoMuestra;
};

#endif // DLGREGLESION_H
