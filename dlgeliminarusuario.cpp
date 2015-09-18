#include "dlgeliminarusuario.h"
#include "ui_dlgeliminarusuario.h"

dlgEliminarUsuario::dlgEliminarUsuario(QString cedulaUsuarioS, QString claveUsuario, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgEliminarUsuario)
{
    ui->setupUi(this);

    cedula = cedulaUsuarioS;
    clave = claveUsuario;

    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->setFixedSize(this->size());
}

dlgEliminarUsuario::~dlgEliminarUsuario()
{
    delete ui;
}

void dlgEliminarUsuario::on_btnCancelar_clicked()
{
    close();
}

void dlgEliminarUsuario::on_btnEliminar_clicked()
{
    dlgConfirmarClave confirmar(clave);

    connect(&confirmar, &dlgConfirmarClave::claveIntroducida, this, &dlgEliminarUsuario::on_claveIntroducida);
    confirmar.exec();
}

void dlgEliminarUsuario::on_claveIntroducida(bool correcta)
{
    if(correcta){
        QSqlQuery query;

        query.prepare("DELETE FROM spectradb.usuario WHERE cedula = '" + cedula + "'");

        query.exec();

        QMessageBox::information(this, "Usuario eliminado", "Se ha eliminado el usuario correctamente.");

        close();

        emit usuarioEliminado();
    }else{
        QMessageBox::critical(this, "Contraseña incorrecta", "La contraseña que introdujo es incorrecta.");
    }
}
