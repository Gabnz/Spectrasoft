#include "dlgregfototipo.h"
#include "ui_dlgregfototipo.h"

dlgRegFototipo::dlgRegFototipo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgRegFototipo)
{
    ui->setupUi(this);

    fototipo = 0;
    ui->btnRegistrar->setEnabled(false);

    QRegExp rx("^([a-zA-Z]+([ ]?[a-zA-Z]?[a-zA-Z]+)*)$");
    QValidator *soloPalabras = new QRegExpValidator(rx, this);
    ui->lineaNombre->setValidator(soloPalabras);
    ui->lineaArea->setValidator(soloPalabras);

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

dlgRegFototipo::~dlgRegFototipo()
{
    delete ui;
}

void dlgRegFototipo::on_btnCancelar_clicked()
{
    close();
}

void dlgRegFototipo::on_lineaNombre_textChanged(const QString &arg1)
{
    ui->lineaNombre->setText(arg1.toUpper());
}

void dlgRegFototipo::on_lineaArea_textChanged(const QString &arg1)
{
    ui->lineaArea->setText(arg1.toUpper());
}

void dlgRegFototipo::on_btnFototipo_clicked()
{
    SpectralOps ops;

    int recomendacion = ops.fototipo();

    dlgFototipo f(fototipo, recomendacion);

    connect(&f, &dlgFototipo::fototipoSeleccionado, this, &dlgRegFototipo::on_fototipo);
    connect(&f, &dlgFototipo::resetearFototipo, this, &dlgRegFototipo::on_resetearFototipo);

    f.exec();
}

void dlgRegFototipo::on_resetearFototipo()
{
    fototipo = 0;
    ui->etqNumeroElegido->setText("N/A");
    ui->etqFototipoElegido->setPixmap(QPixmap::fromImage(QImage(":/img/vacio.png")));
}

void dlgRegFototipo::on_fototipo(int numero)
{
    fototipo = numero;
    ui->etqNumeroElegido->setText(QString().setNum(numero));
    ui->etqFototipoElegido->setPixmap(QPixmap::fromImage(QImage(":/img/fototipo_" + QString().setNum(numero) + ".png")));
}
