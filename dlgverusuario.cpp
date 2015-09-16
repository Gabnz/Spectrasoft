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
    ui->etqFechaNac->setText(QDate::fromString(infoUsuario["fecha_nac"], "yyyy-MM-dd").toString("dd-MM-yyyy"));

    if(infoUsuario["sexo"] == "F"){
        ui->etqSexo->setText("Femenino");
    }else{
        ui->etqSexo->setText("Masculino");
    }

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
