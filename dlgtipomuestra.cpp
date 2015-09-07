#include "dlgtipomuestra.h"
#include "ui_dlgtipomuestra.h"

dlgTipoMuestra::dlgTipoMuestra(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgTipoMuestra)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

dlgTipoMuestra::~dlgTipoMuestra()
{
    delete ui;
}

void dlgTipoMuestra::on_btnCancelar_clicked()
{
    close();
}

void dlgTipoMuestra::on_btnFototipo_clicked()
{
    close();
    emit tipo_muestra("fototipo");
}

void dlgTipoMuestra::on_btnLesion_clicked()
{
    close();
    emit tipo_muestra("lesion");
}
