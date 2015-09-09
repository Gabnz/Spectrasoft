#include "dlgverlesion.h"
#include "ui_dlgverlesion.h"

dlgVerLesion::dlgVerLesion(QHash<QString, QString> infoLesion, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgVerLesion)
{
    ui->setupUi(this);

    ui->etqIdMuestra->setText(infoLesion["id_muestra"]);
    ui->etqTipoMuestra->setText("Lesión");
    ui->etqNombreMuestra->setText(infoLesion["nombre_muestra"]);
    ui->etqAreaMuestra->setText(infoLesion["area_muestra"]);
    ui->etqFechaMuestra->setText(QDate::fromString(infoLesion["fecha_muestra"], "yyyy-MM-dd").toString("dd-MM-yyyy"));

    if(infoLesion.contains("observaciones")){
        ui->editObservaciones->setPlainText(infoLesion["observaciones"]);
    }

    this->adjustSize();
    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

dlgVerLesion::~dlgVerLesion()
{
    delete ui;
}

void dlgVerLesion::on_btnListo_clicked()
{
    close();
}
