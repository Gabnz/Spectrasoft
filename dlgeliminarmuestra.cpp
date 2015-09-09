#include "dlgeliminarmuestra.h"
#include "ui_dlgeliminarmuestra.h"

dlgEliminarMuestra::dlgEliminarMuestra(QString idMuestra, QString claveUsuario, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgEliminarMuestra)
{
    ui->setupUi(this);

    id = idMuestra;
    clave = claveUsuario;

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

dlgEliminarMuestra::~dlgEliminarMuestra()
{
    delete ui;
}

void dlgEliminarMuestra::on_btnCancelar_clicked()
{
    close();
}

void dlgEliminarMuestra::on_btnEliminar_clicked()
{
    dlgConfirmarClave confirmar(clave);

    connect(&confirmar, &dlgConfirmarClave::claveIntroducida, this, &dlgEliminarMuestra::on_claveIntroducida);

    confirmar.exec();
}

void dlgEliminarMuestra::on_claveIntroducida(bool correcta)
{
    if(correcta){

        QSqlQuery query;

        query.prepare("DELETE FROM spectradb.muestra WHERE id_muestra = '" + id + "'");

        query.exec();

        QMessageBox::information(this, "Muestra eliminada", "Se ha eliminado la muestra correctamente.");

        close();

        emit muestraEliminada();
    }else{
        QMessageBox::critical(this, "Contraseña incorrecta", "La contraseña que introdujo es incorrecta.");
    }
}
