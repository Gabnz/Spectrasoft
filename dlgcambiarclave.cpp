#include "dlgcambiarclave.h"
#include "ui_dlgcambiarclave.h"

dlgCambiarClave::dlgCambiarClave(QString cedulaUsuario, QString claveOriginal, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgCambiarClave)
{
    ui->setupUi(this);

    claveActualLista = claveNuevaLista = false;
    cedula = cedulaUsuario;
    clave = claveOriginal;
    claveValida.setPattern("^((?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).{8,16})$");

    revisionBtn();

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

void dlgCambiarClave::revisionBtn()
{
    if(claveActualLista && claveNuevaLista){
        ui->btnCambiar->setEnabled(true);
    }else{
        ui->btnCambiar->setEnabled(false);
    }
}

dlgCambiarClave::~dlgCambiarClave()
{
    delete ui;
}

void dlgCambiarClave::on_btnCancelar_clicked()
{
    close();
}

void dlgCambiarClave::on_lineaClaveActual_textChanged(const QString &arg1)
{
    QRegularExpressionMatch claveMatch = claveValida.match(arg1);

    if(claveMatch.hasMatch()){
        claveActualLista = true;
    }else{
        claveActualLista = false;
    }
    revisionBtn();
}

void dlgCambiarClave::on_lineaClave_textChanged(const QString &arg1)
{
    QRegularExpressionMatch claveMatch = claveValida.match(arg1);

    if(claveMatch.hasMatch()){
        ui->etqClaveValida->setPixmap(QPixmap::fromImage(QImage(":/img/correcto.png")));

        if(!ui->lineaRepetir->text().isEmpty() && ui->lineaRepetir->text() == arg1){
            ui->etqRepetirValida->setPixmap(QPixmap::fromImage(QImage(":/img/correcto.png")));
            claveNuevaLista = true;
        }else{
            ui->etqRepetirValida->setPixmap(QPixmap::fromImage(QImage(":/img/incorrecto.png")));
            claveNuevaLista = false;
        }

    }else{
        ui->etqClaveValida->setPixmap(QPixmap::fromImage(QImage(":/img/incorrecto.png")));

        if(!ui->lineaRepetir->text().isEmpty()){
            ui->etqRepetirValida->setPixmap(QPixmap::fromImage(QImage(":/img/incorrecto.png")));
        }
        claveNuevaLista = false;
    }
    revisionBtn();
}

void dlgCambiarClave::on_lineaRepetir_textChanged(const QString &arg1)
{
    QRegularExpressionMatch claveMatch = claveValida.match(arg1);

   if(arg1 == ui->lineaClave->text() && claveMatch.hasMatch()){
       ui->etqRepetirValida->setPixmap(QPixmap::fromImage(QImage(":/img/correcto.png")));
       claveNuevaLista = true;
   }else{
       claveNuevaLista = false;
       ui->etqRepetirValida->setPixmap(QPixmap::fromImage(QImage(":/img/incorrecto.png")));
   }
   revisionBtn();
}

void dlgCambiarClave::on_btnCambiar_clicked()
{
    if(ui->lineaClaveActual->text() == clave){

        QString consulta = "UPDATE spectradb.usuario SET clave = '" + ui->lineaClave->text() + "' WHERE cedula = '" + cedula + "'";
        QSqlQuery query;
        query.prepare(consulta);
        if(query.exec()){
            QMessageBox::information(this, "contraseña cambiada", "Se ha cambiado la contraseña correctamente.");
            close();
            emit claveCambiada(ui->lineaClave->text());
        }else{
            qDebug() << query.lastError();
        }


    }else{
        QMessageBox::critical(this, "Error al cambiar contraseña", "La contraseña actual que introdujo no es la correcta.");
        ui->lineaClaveActual->clear();
        ui->lineaClave->clear();
        ui->lineaRepetir->clear();
        ui->etqClaveValida->setPixmap(QPixmap::fromImage(QImage(":/img/vacio.png")));
        ui->etqRepetirValida->setPixmap(QPixmap::fromImage(QImage(":/img/vacio.png")));
        claveActualLista = false;
        claveNuevaLista = false;
        revisionBtn();
    }
}
