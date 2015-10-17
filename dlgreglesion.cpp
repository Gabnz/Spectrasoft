#include "dlgreglesion.h"
#include "ui_dlgreglesion.h"

dlgRegLesion::dlgRegLesion(QString claveUsuario, QString usuario, QString historia, QVector<float> datosEspectralesExt, QVector<float> XYZExt, QVector<float> LABExt, QVector<float> absorcionExt, float eritemaExt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgRegLesion)
{
    ui->setupUi(this);

    infoMuestra.clear();
    clave = claveUsuario;
    id_usuario = usuario;
    id_historia = historia;
    datosEspectrales = datosEspectralesExt;
    XYZ = XYZExt;
    LAB = LABExt;
    datosAbsorcion = absorcionExt;
    eritema = eritemaExt;
    ui->btnRegistrar->setEnabled(false);

    QRegExp rx("^([a-zA-Z]+([ ]?[a-zA-Z]?[a-zA-Z]+)*)$");
    QValidator *soloPalabras = new QRegExpValidator(rx, this);
    ui->lineaNombre->setValidator(soloPalabras);
    ui->lineaArea->setValidator(soloPalabras);

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

bool dlgRegLesion::camposListos()
{
    return !ui->lineaNombre->text().isEmpty() && !ui->lineaArea->text().isEmpty();
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

    if(camposListos()){
        ui->btnRegistrar->setEnabled(true);
    }else{
        ui->btnRegistrar->setEnabled(false);
    }
}

void dlgRegLesion::on_lineaArea_textChanged(const QString &arg1)
{
    ui->lineaArea->setText(arg1.toUpper());

    if(camposListos()){
        ui->btnRegistrar->setEnabled(true);
    }else{
        ui->btnRegistrar->setEnabled(false);
    }
}

void dlgRegLesion::on_btnRegistrar_clicked()
{
    dlgConfirmarClave confirmar(clave);

    connect(&confirmar, &dlgConfirmarClave::claveIntroducida, this, &dlgRegLesion::on_claveIntroducida);

    confirmar.exec();
}

void dlgRegLesion::on_claveIntroducida(bool correcta)
{
    if(correcta){
        QString consulta;
        QSqlQuery query;

        consulta = "INSERT INTO spectradb.datos_espectrales(";

        int rango = 400;

        for(int i = 0; i < 31; ++i){

            if(i>0){
                consulta+=", ";
            }

            consulta+= "nm_" + QString().setNum(rango);
            rango+=10;
        }

        consulta+= ") VALUES(";
        rango = 400;

        for(int i = 0; i < 31; ++i){

            if(i>0){
                consulta+=", ";
            }

            consulta+= ":nm_" + QString().setNum(rango);
            rango+=10;
        }

        consulta+= ")";
        query.prepare(consulta);
        rango = 400;

        for(int i = 0; i < 31; ++i){
            query.bindValue(":nm_" + QString().setNum(rango), datosEspectrales[i]);
            rango+=10;
        }

        if(query.exec()){
            id_datos_espectrales = query.lastInsertId().toString();
            query.clear();
            consulta = "INSERT INTO spectradb.datos_absorcion(datos_espectrales, ";
            rango = 400;

            for(int i = 0; i < 31; ++i){

                if(i>0){
                    consulta+=", ";
                }

                consulta+= "nm_" + QString().setNum(rango);
                rango+=10;
            }

            consulta+= ") VALUES(:datos_espectrales, ";
            rango = 400;

            for(int i = 0; i < 31; ++i){

                if(i>0){
                    consulta+=", ";
                }

                consulta+= ":nm_" + QString().setNum(rango);
                rango+=10;
            }

            consulta+= ")";
            query.prepare(consulta);
            rango = 400;

            query.bindValue(":datos_espectrales", id_datos_espectrales);

            for(int i = 0; i < 31; ++i){
                query.bindValue(":nm_" + QString().setNum(rango), datosEspectrales[i]);
                rango+=10;
            }
            query.exec();
            query.clear();

            consulta = "INSERT INTO spectradb.datos_adicionales(datos_espectrales, cie_x, cie_y, cie_z, cie_l, cie_a, cie_b, "
                       "indice_eritema) VALUES(:datos_espectrales, :X, :Y, :Z, "
                       ":L, :A, :B, :eritema)";

            query.prepare(consulta);
            query.bindValue(":datos_espectrales", id_datos_espectrales);
            query.bindValue(":X", XYZ[0]);
            query.bindValue(":Y", XYZ[1]);
            query.bindValue(":Z", XYZ[2]);
            query.bindValue(":L", LAB[0]);
            query.bindValue(":A", LAB[1]);
            query.bindValue(":B", LAB[2]);
            query.bindValue(":eritema", eritema);

            if(!query.exec()){
                qDebug() << "Problema al registrar lesion";
                qDebug() << query.lastError().number();
            }

            query.clear();
            infoMuestra["tipo_muestra"] = "lesion";
            infoMuestra["fecha_muestra"] = QDate::currentDate().toString("yyyy-MM-dd");
            infoMuestra["nombre_muestra"] = ui->lineaNombre->text();
            infoMuestra["area_muestra"] = ui->lineaArea->text();

            if(!ui->textEditObservaciones->toPlainText().isEmpty()){
                infoMuestra["observaciones"] = ui->textEditObservaciones->toPlainText();
            }

            infoMuestra["usuario"] = id_usuario;
            infoMuestra["historia"] = id_historia;
            infoMuestra["datos_espectrales"] = id_datos_espectrales;

            consulta = "INSERT INTO spectradb.muestra(tipo_muestra, fecha_muestra, nombre_muestra, area_muestra, usuario, historia, datos_espectrales";

            if(infoMuestra.contains("observaciones")){
                consulta+= ", observaciones";
            }

            consulta+= ") VALUES(:tipo_muestra, :fecha_muestra, :nombre_muestra, :area_muestra, :usuario, :historia, :datos_espectrales";

            if(infoMuestra.contains("observaciones")){
                consulta+= ", :observaciones";
            }

            consulta+= ")";

            query.prepare(consulta);

            query.bindValue(":tipo_muestra", infoMuestra["tipo_muestra"]);
            query.bindValue(":fecha_muestra", infoMuestra["fecha_muestra"]);
            query.bindValue(":nombre_muestra", infoMuestra["nombre_muestra"]);
            query.bindValue(":area_muestra", infoMuestra["area_muestra"]);
            query.bindValue(":usuario", infoMuestra["usuario"]);
            query.bindValue(":historia", infoMuestra["historia"]);
            query.bindValue(":datos_espectrales", infoMuestra["datos_espectrales"]);

            if(infoMuestra.contains("observaciones")){
                query.bindValue(":observaciones", infoMuestra["observaciones"]);
            }

            if(query.exec()){
                infoMuestra["id_muestra"] = query.lastInsertId().toString();
                QMessageBox::information(this, "Muestra registrada", "Se ha registrado la muestra correctamente.");
                close();
                emit lesion_registrada(infoMuestra);
            }else{
                qDebug() << query.lastError();
            }
        }else{
            qDebug() << query.lastError();
        }
    }else{
        QMessageBox::critical(this, "Contraseña incorrecta", "La contraseña que introdujo es incorrecta.");
    }
}
