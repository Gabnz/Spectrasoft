#include "dlgeliminarhistoria.h"
#include "ui_dlgeliminarhistoria.h"

dlgEliminarHistoria::dlgEliminarHistoria(QString idHistoria, QString claveUsuario, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgEliminarHistoria)
{
    ui->setupUi(this);
    id = idHistoria;
    clave = claveUsuario;
    historiaEliminada = false;

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

bool dlgEliminarHistoria::getHistoriaEliminada()
{
    return historiaEliminada;
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

    confirmarC.exec();

    if(confirmarC.getClaveCorrecta()){

        QSqlQuery query;

        query.prepare("DELETE FROM spectradb.historia WHERE id_historia = '" + id + "'");

        query.exec();

        QMessageBox::information(this, "Historia eliminada", "Se ha eliminado la historia correctamente.");
        historiaEliminada = true;
        close();
    }else{
        QMessageBox::critical(this, "Contraseña incorrecta", "La contraseña que introdujo es incorrecta.");
        historiaEliminada = false;
    }
}
