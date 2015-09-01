#include "dlgreghistoria.h"
#include "ui_dlgreghistoria.h"

dlgRegHistoria::dlgRegHistoria(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgRegHistoria)
{
    ui->setupUi(this);

    QDate fechaMinima, fechaDefecto;
    fechaMinima = fechaDefecto = QDate::currentDate();
    fechaMinima.setDate(fechaMinima.year() - 120,fechaMinima.month(), fechaMinima.day() );
    fechaDefecto.setDate(fechaDefecto.year() - 18, fechaMinima.month(), fechaMinima.day());
    ui->editFechaNac->setDate(fechaDefecto);
    ui->editFechaNac->setDateRange(fechaMinima, QDate::currentDate());

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

dlgRegHistoria::~dlgRegHistoria()
{
    delete ui;
}

void dlgRegHistoria::on_btnCancelar_clicked()
{
    close();
}

void dlgRegHistoria::on_lineaNombre_textChanged(const QString &arg1)
{
}

void dlgRegHistoria::on_lineaApellido_textChanged(const QString &arg1)
{
}
