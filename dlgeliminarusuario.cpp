#include "dlgeliminarusuario.h"
#include "ui_dlgeliminarusuario.h"

dlgEliminarUsuario::dlgEliminarUsuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgEliminarUsuario)
{
    ui->setupUi(this);

    ui->btnEliminar->setEnabled(false);
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
