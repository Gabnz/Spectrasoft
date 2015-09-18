#ifndef DLGCAMBIARROL_H
#define DLGCAMBIARROL_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <dlgconfirmarclave.h>

namespace Ui {
class dlgCambiarRol;
}

class dlgCambiarRol : public QDialog
{
    Q_OBJECT

public:
    explicit dlgCambiarRol(QString cedulaUsuarioS, QString claveUsuario, QString rolOriginal, QWidget *parent = 0);
    void revisionBtn();
    ~dlgCambiarRol();

signals:
    void rolCambiado(QString rol);

private slots:
    void on_cBoxRol_currentTextChanged(const QString &arg1);

    void on_btnCancelar_clicked();

    void on_btnCambiar_clicked();

    void on_claveIntroducida(bool correcta);

private:
    Ui::dlgCambiarRol *ui;
    QString cedula, clave, rol;
};

#endif // DLGCAMBIARROL_H
