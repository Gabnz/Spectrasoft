#include "dlggrafica.h"
#include "ui_dlggrafica.h"

dlgGrafica::dlgGrafica(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgGrafica)
{
    ui->setupUi(this);
}

dlgGrafica::~dlgGrafica()
{
    delete ui;
}
