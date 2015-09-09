#include "dlgeliminarhistoria.h"
#include "ui_dlgeliminarhistoria.h"

dlgEliminarHistoria::dlgEliminarHistoria(QString idHistoria, QString claveUsuario, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgEliminarHistoria)
{
    ui->setupUi(this);

    id = idHistoria;
    clave = claveUsuario;

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

dlgEliminarHistoria::~dlgEliminarHistoria()
{
    delete ui;
}

void dlgEliminarHistoria::on_btnCancelar_clicked()
{
    close();
}

void dlgEliminarHistoria::on_btnEliminar_clicked()
{
    dlgConfirmarClave confirmarC(clave);

    connect(&confirmarC, &dlgConfirmarClave::claveIntroducida, this, &dlgEliminarHistoria::on_claveIntroducida);

    confirmarC.exec();
}

void dlgEliminarHistoria::on_claveIntroducida(bool correcta)
{
    if(correcta){
        QSqlQuery query;

        query.prepare("DELETE FROM spectradb.historia WHERE id_historia = '" + id + "'");

        query.exec();

        QMessageBox::information(this, "Historia eliminada", "Se ha eliminado la historia correctamente.");

        close();

        emit historiaEliminada();
    }else{
        QMessageBox::critical(this, "Contraseña incorrecta", "La contraseña que introdujo es incorrecta.");
    }
}
