#ifndef DLGINICIOSESION_H
#define DLGINICIOSESION_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QRegularExpression>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDate>

namespace Ui {
class dlgInicioSesion;
}

class dlgInicioSesion : public QDialog
{
    Q_OBJECT

public:
    explicit dlgInicioSesion(QWidget *parent = 0);
    ~dlgInicioSesion();

signals:
    void sesion_iniciada(QHash<QString, QString> info);

private slots:
    void on_lineaUsuario_textChanged(const QString &arg1);

    void on_lineaClave_textChanged(const QString &arg1);

    void on_btnIngresar_clicked();

private:
    Ui::dlgInicioSesion *ui;
    bool usuario, clave;
    QHash<QString, QString> infoUsuario;
    QRegularExpression usuarioValido, claveValida;
};

#endif // DLGINICIOSESION_H
