#include "dlgvermuestra.h"
#include "ui_dlgvermuestra.h"

dlgVerMuestra::dlgVerMuestra(QHash<QString, QString> infoMuestra, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgVerMuestra)
{
    ui->setupUi(this);

    ui->etqIdMuestra->setText(infoMuestra["id_muestra"]);

    if(infoMuestra["tipo_muestra"] == "lesion")
        ui->etqTipoMuestra->setText("Lesión");
    else
        ui->etqTipoMuestra->setText("Fototipo");

    ui->etqNombreMuestra->setText(infoMuestra["nombre_muestra"]);
    ui->etqAreaMuestra->setText(infoMuestra["area_muestra"]);
    ui->etqFechaMuestra->setText(QDate::fromString(infoMuestra["fecha_muestra"], "yyyy-MM-dd").toString("dd-MM-yyyy"));

    if(infoMuestra.contains("observaciones")){
        ui->editObservaciones->setPlainText(infoMuestra["observaciones"]);
    }

    this->adjustSize();
    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

dlgVerMuestra::~dlgVerMuestra()
{
    delete ui;
}

void dlgVerMuestra::on_btnListo_clicked()
{
    close();
}
