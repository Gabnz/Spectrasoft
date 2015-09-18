#include "dlgmodificarusuario.h"
#include "ui_dlgmodificarusuario.h"

dlgModificarUsuario::dlgModificarUsuario(QHash<QString, QString> infoUsuario, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgModificarUsuario)
{
    ui->setupUi(this);

    infoOriginal = infoUsuario;
    infoNueva.clear();

    QRegExp rx("^([a-zA-Z]+([ ]?[a-zA-Z]?[a-zA-Z]+)*)$");
    QValidator *soloPalabras = new QRegExpValidator(rx, this);
    ui->lineaNombre->setValidator(soloPalabras);
    ui->lineaApellido->setValidator(soloPalabras);

    QDate fechaMinima;
    fechaMinima =  QDate::currentDate();
    fechaMinima.setDate(fechaMinima.year() - 120,fechaMinima.month(), fechaMinima.day() );
    ui->editFechaNac->setDateRange(fechaMinima, QDate::currentDate());
    ui->lineaNombre->setText(infoUsuario["nombre"]);
    ui->lineaApellido->setText(infoUsuario["apellido"]);
    ui->editFechaNac->setDate(QDate::fromString(infoUsuario["fecha_nac"], "yyyy-MM-dd"));

    if(infoUsuario["sexo"] == "F"){
        ui->cBoxSexo->setCurrentText("Femenino");
    }else{
        ui->cBoxSexo->setCurrentText("Masculino");
    }

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

void dlgModificarUsuario::revisionBtn()
{
    if(!infoNueva.isEmpty()){
        ui->btnModificar->setEnabled(true);
    }else{
        ui->btnModificar->setEnabled(false);
    }
}

dlgModificarUsuario::~dlgModificarUsuario()
{
    delete ui;
}

void dlgModificarUsuario::on_btnCancelar_clicked()
{
    close();
}

void dlgModificarUsuario::on_lineaNombre_textChanged(const QString &arg1)
{
    ui->lineaNombre->setText(arg1.toUpper());

    if(!ui->lineaNombre->text().isEmpty() && ui->lineaNombre->text().length() >= 3 && ui->lineaNombre->text() != infoOriginal["nombre"]){
        infoNueva["nombre"] = ui->lineaNombre->text();
    }else{
        if(infoNueva.contains("nombre")){
            infoNueva.remove("nombre");
        }
    }

    revisionBtn();
}

void dlgModificarUsuario::on_lineaApellido_textChanged(const QString &arg1)
{
    ui->lineaApellido->setText(arg1.toUpper());

    if(!ui->lineaApellido->text().isEmpty() && ui->lineaApellido->text().length() >= 3 && ui->lineaApellido->text() != infoOriginal["apellido"]){
        infoNueva["apellido"] = ui->lineaApellido->text();
    }else{
        if(infoNueva.contains("apellido")){
            infoNueva.remove("apellido");
        }
    }

    revisionBtn();
}

void dlgModificarUsuario::on_editFechaNac_dateChanged(const QDate &date)
{
    if(date.toString("yyyy-MM-dd") != infoOriginal["fecha_nac"]){
        infoNueva["fecha_nac"] = date.toString("yyyy-MM-dd");
    }else{
        if(infoNueva.contains("fecha_nac")){
            infoNueva.remove("fecha_nac");
        }
    }

    revisionBtn();
}

void dlgModificarUsuario::on_cBoxSexo_currentTextChanged(const QString &arg1)
{
    QString aux;

    if(arg1 == "Femenino"){
        aux = "F";
    }else{
        aux = "M";
    }

    if(aux != infoOriginal["sexo"]){
        infoNueva["sexo"] = aux;
    }else{
        if(infoNueva.contains("sexo")){
            infoNueva.remove("sexo");
        }
    }

    revisionBtn();
}

void dlgModificarUsuario::on_btnModificar_clicked()
{
    dlgConfirmarClave confirmar(infoOriginal["clave"]);

    connect(&confirmar, &dlgConfirmarClave::claveIntroducida, this, &dlgModificarUsuario::on_claveIntroducida);
    confirmar.exec();
}

void dlgModificarUsuario::on_claveIntroducida(bool correcta)
{
    if(correcta){
        QString consulta = "UPDATE spectradb.usuario SET ";
        bool varios = false;

        if(infoNueva.contains("nombre")){
            consulta+= "nombre = '" + infoNueva["nombre"] + "'";
            varios = true;
        }

        if(infoNueva.contains("apellido")){
            if(varios){
                consulta+= ", ";
            }
            consulta+= "apellido = '" + infoNueva["apellido"] + "'";
            varios = true;
        }

        if(infoNueva.contains("fecha_nac")){
            if(varios){
                consulta+= ", ";
            }
            consulta+= "fecha_nac = '" + infoNueva["fecha_nac"] + "'";
            varios = true;
        }

        if(infoNueva.contains("sexo")){
            if(varios){
                consulta+= ", ";
            }
            consulta+= "sexo = '" + infoNueva["sexo"] + "'";
        }

        consulta+= " WHERE cedula = '" + infoOriginal["cedula"] + "'";

        QSqlQuery query;

        query.prepare(consulta);
        if(query.exec()){

            QMessageBox::information(this, "Usuario modificado", "Se ha modificado el usuario correctamente.");
            close();

            QHash<QString, QString> infoResultante;
            QStringList llaves, valores;

            llaves = infoNueva.keys();
            valores = infoNueva.values();

            infoResultante = infoOriginal;

            for(int i = 0; i < infoNueva.size(); ++i){
                infoResultante[llaves[i]] = valores[i];
            }

            emit usuarioModificado(infoResultante);

        }else{
            qDebug() << query.lastError();
        }
    }else{
        QMessageBox::critical(this, "Contraseña incorrecta", "La contraseña que introdujo es incorrecta.");
    }
}
