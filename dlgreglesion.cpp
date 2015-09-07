#include "dlgreglesion.h"
#include "ui_dlgreglesion.h"

dlgRegLesion::dlgRegLesion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgRegLesion)
{
    ui->setupUi(this);

    ui->btnRegistrar->setEnabled(false);

    QRegExp rx("^([a-zA-Z]+([ ]?[a-zA-Z]?[a-zA-Z]+)*)$");
    QValidator *soloPalabras = new QRegExpValidator(rx, this);
    ui->lineaNombre->setValidator(soloPalabras);
    ui->lineaArea->setValidator(soloPalabras);

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

dlgRegLesion::~dlgRegLesion()
{
    delete ui;
}

void dlgRegLesion::on_btnCancelar_clicked()
{
    close();
}

void dlgRegLesion::on_lineaNombre_textChanged(const QString &arg1)
{
    ui->lineaNombre->setText(arg1.toUpper());
}

void dlgRegLesion::on_lineaArea_textChanged(const QString &arg1)
{
    ui->lineaArea->setText(arg1.toUpper());
}
