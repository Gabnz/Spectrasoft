#ifndef DLGCAMBIARCLAVE_H
#define DLGCAMBIARCLAVE_H

#include <QDialog>
#include <QRegularExpression>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

namespace Ui {
class dlgCambiarClave;
}

class dlgCambiarClave : public QDialog
{
    Q_OBJECT

public:
    explicit dlgCambiarClave(QString cedulaUsuario, QString claveOriginal, QWidget *parent = 0);
    void revisionBtn();
    ~dlgCambiarClave();

signals:
    void claveCambiada(QString info);

private slots:
    void on_btnCancelar_clicked();

    void on_lineaClaveActual_textChanged(const QString &arg1);

    void on_lineaClave_textChanged(const QString &arg1);

    void on_lineaRepetir_textChanged(const QString &arg1);

    void on_btnCambiar_clicked();

private:
    Ui::dlgCambiarClave *ui;
    QRegularExpression claveValida;
    QString cedula, clave;
    bool claveActualLista, claveNuevaLista;
};

#endif // DLGCAMBIARCLAVE_H
