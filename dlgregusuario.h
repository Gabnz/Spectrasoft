#ifndef DLGREGUSUARIO_H
#define DLGREGUSUARIO_H

#include <QDialog>
#include <QRegularExpression>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class dlgRegUsuario;
}

class dlgRegUsuario : public QDialog
{
    Q_OBJECT

public:
    explicit dlgRegUsuario(QWidget *parent = 0);
    bool camposListos();
    ~dlgRegUsuario();

private slots:
    void on_btnCancelar_clicked();

    void on_lineaNombre_textChanged(const QString &arg1);

    void on_lineaApellido_textChanged(const QString &arg1);

    void on_lineaCI_textChanged(const QString &arg1);

    void on_cBoxRol_currentIndexChanged(int index);

    void on_lineaClave_textChanged(const QString &arg1);

    void on_lineaRepetirClave_textChanged(const QString &arg1);

    void on_cBoxSexo_currentIndexChanged(int index);

    void on_btnRegistrar_clicked();

private:
    Ui::dlgRegUsuario *ui;
    bool nombreListo, apellidoListo, cedulaLista, rolListo, claveLista, fecha_nacLista, sexoListo;
    QRegularExpression claveValida;
    QHash<QString, QString> infoUsuario;
};

#endif // DLGREGUSUARIO_H
