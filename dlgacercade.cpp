#include "dlgacercade.h"
#include "ui_dlgacercade.h"

dlgAcercaDe::dlgAcercaDe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgAcercaDe)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

dlgAcercaDe::~dlgAcercaDe()
{
    delete ui;
}

void dlgAcercaDe::on_btnCerrar_clicked()
{
    close();
}
