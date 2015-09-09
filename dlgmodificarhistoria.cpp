#include "dlgmodificarhistoria.h"
#include "ui_dlgmodificarhistoria.h"

dlgModificarHistoria::dlgModificarHistoria(QString claveUsuario, QHash<QString, QString> infoHistoria, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgModificarHistoria)
{
    ui->setupUi(this);

    clave = claveUsuario;
    infoOriginal = infoHistoria;
    infoNueva.clear();

    QRegExp rx("^([a-zA-Z]+([ ]?[a-zA-Z]?[a-zA-Z]+)*)$");
    QValidator *soloPalabras = new QRegExpValidator(rx, this);
    ui->lineaNombre->setValidator(soloPalabras);
    ui->lineaApellido->setValidator(soloPalabras);

    QValidator *soloNumeros = new QIntValidator(1, 999999999, this);
    ui->lineaCI->setValidator(soloNumeros);

    QDate fechaMinima;
    fechaMinima =  QDate::currentDate();
    fechaMinima.setDate(fechaMinima.year() - 120,fechaMinima.month(), fechaMinima.day() );
    ui->editFechaNac->setDateRange(fechaMinima, QDate::currentDate());
    ui->lineaNombre->setText(infoHistoria["nombre"]);
    ui->lineaApellido->setText(infoHistoria["apellido"]);
    ui->editFechaNac->setDate(QDate::fromString(infoHistoria["fecha_nac"], "yyyy-MM-dd"));

    if(infoHistoria.contains("cedula")){
        QString aux = infoHistoria["cedula"];

        if(infoHistoria["cedula"].contains("V")){
            ui->cBoxCI->setCurrentText("V");
            aux.remove("V");
        }else{
            ui->cBoxCI->setCurrentText("E");
            aux.remove("E");
        }
        ui->lineaCI->setText(aux);
    }

    if(infoHistoria["sexo"] == "F"){
        ui->cBoxSexo->setCurrentText("Femenino");
    }else{
        ui->cBoxSexo->setCurrentText("Masculino");
    }

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

dlgModificarHistoria::~dlgModificarHistoria()
{
    delete ui;
}

void dlgModificarHistoria::on_btnCancelar_clicked()
{
    close();
}

void dlgModificarHistoria::on_lineaNombre_textChanged(const QString &arg1)
{
    ui->lineaNombre->setText(arg1.toUpper());

    if(!ui->lineaNombre->text().isEmpty() && ui->lineaNombre->text().length() >= 3 && ui->lineaNombre->text() != infoOriginal["nombre"]){
        infoNueva["nombre"] = ui->lineaNombre->text();
    }else{
        if(infoNueva.contains("nombre")){
            infoNueva.remove("nombre");
        }
    }

    if(!infoNueva.isEmpty()){
        ui->btnModificar->setEnabled(true);
    }else{
        ui->btnModificar->setEnabled(false);
    }
}

void dlgModificarHistoria::on_lineaApellido_textChanged(const QString &arg1)
{
    ui->lineaApellido->setText(arg1.toUpper());

    if(!ui->lineaApellido->text().isEmpty() && ui->lineaApellido->text().length() >= 3 && ui->lineaApellido->text() != infoOriginal["apellido"]){
        infoNueva["apellido"] = ui->lineaApellido->text();
    }else{
        if(infoNueva.contains("apellido")){
            infoNueva.remove("apellido");
        }
    }

    if(!infoNueva.isEmpty()){
        ui->btnModificar->setEnabled(true);
    }else{
        ui->btnModificar->setEnabled(false);
    }
}

void dlgModificarHistoria::on_btnModificar_clicked()
{
    dlgConfirmarClave confirmar(clave);

    connect(&confirmar, &dlgConfirmarClave::claveIntroducida, this, &dlgModificarHistoria::on_claveIntroducida);

    confirmar.exec();
}

void dlgModificarHistoria::on_claveIntroducida(bool correcta)
{
    if(correcta){
        QString consulta = "UPDATE spectradb.historia SET ";
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

        if(infoNueva.contains("cedula")){
            if(varios){
                consulta+= ", ";
            }
            consulta+= "cedula = ";

            if(infoNueva["cedula"] == ""){
                consulta+= "NULL";
            }else{
                consulta+= "'" + infoNueva["cedula"] + "'";
            }

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
            varios = true;
        }

        consulta+= " WHERE id_historia = '" + infoOriginal["id_historia"] + "'";

        QSqlQuery query;

        query.prepare(consulta);
        if(query.exec()){

            QMessageBox::information(this, "Historia modificada", "Se ha modificado la historia correctamente.");

            close();

            QHash<QString, QString> infoResultante;
            QStringList llaves, valores;

            llaves = infoNueva.keys();
            valores = infoNueva.values();

            infoResultante = infoOriginal;

            for(int i = 0; i < infoNueva.size(); ++i){
                infoResultante[llaves[i]] = valores[i];
            }

            emit historiaModificada(infoResultante);

        }else{
            if(query.lastError().number() == 23505){
                QMessageBox::critical(this, "Error al modificar", "La cédula de identidad " + infoNueva["cedula"] + " ya está siendo utilizada.");

                infoNueva.remove("cedula");

                if(infoOriginal.contains("cedula")){
                    QString aux, aux2;
                    aux2 = infoOriginal["cedula"];

                    if(infoOriginal["cedula"].contains("V")){
                        aux = "V";
                        aux2.remove("V");
                    }else{
                        aux = "E";
                        aux2.remove("E");
                    }
                    ui->cBoxCI->setCurrentText(aux);
                    ui->lineaCI->setText(aux2);
                }else
                    ui->lineaCI->clear();

                ui->btnModificar->setEnabled(false);
            }
        }
    }else{
        QMessageBox::critical(this, "Contraseña incorrecta", "La contraseña que introdujo es incorrecta.");
    }
}

void dlgModificarHistoria::on_cBoxCI_currentTextChanged(const QString &arg1)
{
    QString aux = ui->cBoxCI->currentText() + ui->lineaCI->text();

    if(infoOriginal.contains("cedula")){
        if(aux != infoOriginal["cedula"]){

            if(!ui->lineaCI->text().isEmpty())
                infoNueva["cedula"] = aux;
            else
                infoNueva["cedula"] = "";
        }else{
            if(infoNueva.contains("cedula")){
                infoNueva.remove("cedula");
            }
        }
    }else{
        if(!ui->lineaCI->text().isEmpty())
            infoNueva["cedula"] = aux;
        else{
            if(infoNueva.contains("cedula")){
                infoNueva.remove("cedula");
            }
        }
    }

    if(!infoNueva.isEmpty()){
        ui->btnModificar->setEnabled(true);
    }else{
        ui->btnModificar->setEnabled(false);
    }
}

void dlgModificarHistoria::on_lineaCI_textChanged(const QString &arg1)
{
    QString aux = ui->cBoxCI->currentText() + ui->lineaCI->text();

    if(infoOriginal.contains("cedula")){
        if(aux != infoOriginal["cedula"]){

            if(!ui->lineaCI->text().isEmpty())
                infoNueva["cedula"] = aux;
            else
                infoNueva["cedula"] = "";
        }else{
            if(infoNueva.contains("cedula")){
                infoNueva.remove("cedula");
            }
        }
    }else{
        if(!ui->lineaCI->text().isEmpty())
            infoNueva["cedula"] = aux;
        else{
            if(infoNueva.contains("cedula")){
                infoNueva.remove("cedula");
            }
        }
    }

    if(!infoNueva.isEmpty()){
        ui->btnModificar->setEnabled(true);
    }else{
        ui->btnModificar->setEnabled(false);
    }
}

void dlgModificarHistoria::on_editFechaNac_dateChanged(const QDate &date)
{
    if(date.toString("yyyy-MM-dd") != infoOriginal["fecha_nac"]){
        infoNueva["fecha_nac"] = date.toString("yyyy-MM-dd");
    }else{
        if(infoNueva.contains("fecha_nac")){
            infoNueva.remove("fecha_nac");
        }
    }

    if(!infoNueva.isEmpty()){
        ui->btnModificar->setEnabled(true);
    }else{
        ui->btnModificar->setEnabled(false);
    }
}

void dlgModificarHistoria::on_cBoxSexo_currentTextChanged(const QString &arg1)
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

    if(!infoNueva.isEmpty()){
        ui->btnModificar->setEnabled(true);
    }else{
        ui->btnModificar->setEnabled(false);
    }
}
