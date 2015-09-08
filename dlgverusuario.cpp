#include "dlgverusuario.h"
#include "ui_dlgverusuario.h"

dlgVerUsuario::dlgVerUsuario(QHash<QString, QString> infoUsuario, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgVerUsuario)
{
    ui->setupUi(this);

    QString aux;

    if(infoUsuario["rol"] == "dermatologo")
        aux = "Dermatólogo";
    else if(infoUsuario["rol"] == "investigador")
        aux = "Investigador";
    else
        aux = "Administrador";

    ui->etqRol->setText(aux);
    ui->etqNombre->setText(infoUsuario["nombre"]);
    ui->etqApellido->setText(infoUsuario["apellido"]);
    ui->etqCedula->setText(infoUsuario["cedula"]);
    ui->etqFechaNac->setText(infoUsuario["fecha_nac"]);
    ui->etqSexo->setText(infoUsuario["sexo"]);

    this->adjustSize();
    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

dlgVerUsuario::~dlgVerUsuario()
{
    delete ui;
}

void dlgVerUsuario::on_btnListo_clicked()
{
    close();
}
