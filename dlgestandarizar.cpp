#include "dlgestandarizar.h"
#include "ui_dlgestandarizar.h"

dlgEstandarizar::dlgEstandarizar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgEstandarizar)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->setFixedSize(this->size());
}

void dlgEstandarizar::estBlanco()
{
    ui->etqColor->setPixmap(QPixmap::fromImage(QImage(":/img/color_blanco.png")));
    ui->etqTituloColor->setText("Prepare la cerámica blanca");
}

dlgEstandarizar::~dlgEstandarizar()
{
    delete ui;
}

void dlgEstandarizar::on_btnListo_clicked()
{
    close();
}
