#include "dlgcambiarrol.h"
#include "ui_dlgcambiarrol.h"

dlgCambiarRol::dlgCambiarRol(QString cedulaUsuarioS, QString claveUsuario, QString rolOriginal, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgCambiarRol)
{
    ui->setupUi(this);

    cedula = cedulaUsuarioS;
    clave = claveUsuario;
    rol = rolOriginal;

    if(rol == "administrador"){
        ui->cBoxRol->setCurrentText("Administrador");
    }else if(rol == "dermatologo"){
        ui->cBoxRol->setCurrentText("Dermatólogo");
    }else{
        ui->cBoxRol->setCurrentText("Investigador");
    }

    revisionBtn();

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

void dlgCambiarRol::revisionBtn()
{
    QString aux;

    if(ui->cBoxRol->currentText() == "Administrador"){
        aux = "administrador";
    }else if(ui->cBoxRol->currentText() == "Dermatólogo"){
        aux = "dermatologo";
    }else{
        aux = "investigador";
    }

    if(aux != rol){
        ui->btnCambiar->setEnabled(true);
    }else{
        ui->btnCambiar->setEnabled(false);
    }
}

dlgCambiarRol::~dlgCambiarRol()
{
    delete ui;
}

void dlgCambiarRol::on_cBoxRol_currentTextChanged(const QString &arg1)
{
    revisionBtn();
}

void dlgCambiarRol::on_btnCancelar_clicked()
{
    close();
}

void dlgCambiarRol::on_btnCambiar_clicked()
{
    dlgConfirmarClave confirmar(clave);

    connect(&confirmar, &dlgConfirmarClave::claveIntroducida, this, &dlgCambiarRol::on_claveIntroducida);
    confirmar.exec();
}

void dlgCambiarRol::on_claveIntroducida(bool correcta)
{
    if(correcta){
        QString aux;

        if(ui->cBoxRol->currentText() == "Administrador"){
            aux = "administrador";
        }else if(ui->cBoxRol->currentText() == "Dermatólogo"){
            aux = "dermatologo";
        }else{
            aux = "investigador";
        }

        QString consulta;

        consulta = "UPDATE spectradb.usuario SET rol = '" + aux + "'" + " WHERE cedula = '" + cedula + "'";

        QSqlQuery query;

        query.prepare(consulta);

        if(query.exec()){
            QMessageBox::information(this, "Rol cambiado", "Se ha cambiado el rol de este usuario correctamente.");
            close();
            emit rolCambiado(aux);
        }else{
            qDebug() << query.lastError();
        }
    }else{
        QMessageBox::critical(this, "Contraseña incorrecta", "La contraseña que introdujo es incorrecta.");
    }
}
