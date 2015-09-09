#include "dlgconfirmarclave.h"
#include "ui_dlgconfirmarclave.h"

dlgConfirmarClave::dlgConfirmarClave(QString claveUsuario, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgConfirmarClave)
{
    ui->setupUi(this);

    ui->btnContinuar->setEnabled(false);
    clave = claveUsuario;

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

dlgConfirmarClave::~dlgConfirmarClave()
{
    delete ui;
}

void dlgConfirmarClave::on_lineaClave_textChanged(const QString &arg1)
{
    if(arg1.length() >= 8){
        ui->btnContinuar->setEnabled(true);
    }else{
        ui->btnContinuar->setEnabled(false);
    }
}

void dlgConfirmarClave::on_btnContinuar_clicked()
{
    close();

    if(ui->lineaClave->text() == clave){
        emit claveIntroducida(true);
    }else{
        emit claveIntroducida(false);
    }
}
