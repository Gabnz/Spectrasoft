#include "dlgverhistoria.h"
#include "ui_dlgverhistoria.h"

dlgVerHistoria::dlgVerHistoria(QHash<QString, QString> infoHistoria, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgVerHistoria)
{
    ui->setupUi(this);

    ui->etqHistoria->setText(infoHistoria["id_historia"]);
    ui->etqNombre->setText(infoHistoria["nombre"]);
    ui->etqApellido->setText(infoHistoria["apellido"]);
    ui->etqFechaNac->setText(QDate::fromString(infoHistoria["fecha_nac"], "yyyy-MM-dd").toString("dd-MM-yyyy"));
    ui->etqFechaIng->setText(QDate::fromString(infoHistoria["fecha_ingreso"], "yyyy-MM-dd").toString("dd-MM-yyyy"));

    if(infoHistoria["sexo"] == "F"){
        ui->etqSexo->setText("Femenino");
    }else{
        ui->etqSexo->setText("Masculino");
    }

    if(infoHistoria.contains("cedula")){
        ui->etqCedula->setText(infoHistoria["cedula"]);
    }

    if(infoHistoria.contains("fototipo")){
        ui->etqNumFototipo->setText(infoHistoria["fototipo"]);
        ui->etqFototipo->setPixmap(QPixmap::fromImage(QImage(":img/fototipo_" + infoHistoria["fototipo"] + ".png")));
    }

    this->adjustSize();
    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

dlgVerHistoria::~dlgVerHistoria()
{
    delete ui;
}

void dlgVerHistoria::on_btnListo_clicked()
{
    close();
}
