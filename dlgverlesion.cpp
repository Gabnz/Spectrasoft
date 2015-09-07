#include "dlgverlesion.h"
#include "ui_dlgverlesion.h"

dlgVerLesion::dlgVerLesion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgVerLesion)
{
    ui->setupUi(this);
}

dlgVerLesion::~dlgVerLesion()
{
    delete ui;
}

void dlgVerLesion::on_btnListo_clicked()
{
    close();
}
