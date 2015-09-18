#ifndef DLGELIMINARUSUARIO_H
#define DLGELIMINARUSUARIO_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <dlgconfirmarclave.h>

namespace Ui {
class dlgEliminarUsuario;
}

class dlgEliminarUsuario : public QDialog
{
    Q_OBJECT

public:
    explicit dlgEliminarUsuario(QString cedulaUsuarioS, QString claveUsuario, QWidget *parent = 0);
    ~dlgEliminarUsuario();

signals:
    void usuarioEliminado();

private slots:
    void on_btnCancelar_clicked();

    void on_btnEliminar_clicked();

    void on_claveIntroducida(bool correcta);

private:
    Ui::dlgEliminarUsuario *ui;
    QString cedula, clave;
};

#endif // DLGELIMINARUSUARIO_H
