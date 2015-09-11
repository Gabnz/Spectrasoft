#include "dlgregfototipo.h"
#include "ui_dlgregfototipo.h"

dlgRegFototipo::dlgRegFototipo(QString usuario, QString historia, QVector<float> datosEspectralesExt, QVector<float> XYZExt, QVector<float> LABExt, float absorcionExt, float esparcimientoExt, float eritemaExt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgRegFototipo)
{
    ui->setupUi(this);

    infoMuestra.clear();
    id_usuario = usuario;
    id_historia = historia;
    datosEspectrales = datosEspectralesExt;
    XYZ = XYZExt;
    LAB = LABExt;
    absorcion = absorcionExt;
    esparcimiento = esparcimientoExt;
    eritema = eritemaExt;
    fototipo = 0;
    ui->lineaNombre->setText("FOTOTIPO");
    ui->lineaNombre->setReadOnly(true);
    ui->btnRegistrar->setEnabled(false);

    QRegExp rx("^([a-zA-Z]+([ ]?[a-zA-Z]?[a-zA-Z]+)*)$");
    QValidator *soloPalabras = new QRegExpValidator(rx, this);
    ui->lineaArea->setValidator(soloPalabras);

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

bool dlgRegFototipo::camposListos()
{
    return !ui->lineaArea->text().isEmpty() && fototipo != 0;
}

dlgRegFototipo::~dlgRegFototipo()
{
    delete ui;
}

void dlgRegFototipo::on_btnCancelar_clicked()
{
    close();
}

void dlgRegFototipo::on_lineaArea_textChanged(const QString &arg1)
{
    ui->lineaArea->setText(arg1.toUpper());

    if(camposListos()){
        ui->btnRegistrar->setEnabled(true);
    }else{
        ui->btnRegistrar->setEnabled(false);
    }
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
    ui->btnRegistrar->setEnabled(false);
}

void dlgRegFototipo::on_fototipo(int numero)
{
    fototipo = numero;
    ui->etqNumeroElegido->setText(QString().setNum(numero));
    ui->etqFototipoElegido->setPixmap(QPixmap::fromImage(QImage(":/img/fototipo_" + QString().setNum(numero) + ".png")));

    if(camposListos()){
        ui->btnRegistrar->setEnabled(true);
    }else{
        ui->btnRegistrar->setEnabled(false);
    }
}

void dlgRegFototipo::on_btnRegistrar_clicked()
{
    infoMuestra["tipo_muestra"] = "fototipo";
    infoMuestra["fecha_muestra"] = QDate::currentDate().toString("yyyy-MM-dd");
    infoMuestra["nombre_muestra"] = ui->lineaNombre->text();
    infoMuestra["area_muestra"] = ui->lineaArea->text();

    if(!ui->textEditObservaciones->toPlainText().isEmpty()){
        infoMuestra["observaciones"] = ui->textEditObservaciones->toPlainText();
    }

    infoMuestra["usuario"] = id_usuario;
    infoMuestra["historia"] = id_historia;

    QString consulta;

    consulta = "INSERT INTO spectradb.muestra(tipo_muestra, fecha_muestra, nombre_muestra, area_muestra, usuario, historia";

    if(infoMuestra.contains("observaciones")){
        consulta+= ", observaciones";
    }

    consulta+= ") VALUES(:tipo_muestra, :fecha_muestra, :nombre_muestra, :area_muestra, :usuario, :historia";

    if(infoMuestra.contains("observaciones")){
        consulta+= ", :observaciones";
    }

    consulta+= ")";

    QSqlQuery query;

    query.prepare(consulta);

    query.bindValue(":tipo_muestra", infoMuestra["tipo_muestra"]);
    query.bindValue(":fecha_muestra", infoMuestra["fecha_muestra"]);
    query.bindValue(":nombre_muestra", infoMuestra["nombre_muestra"]);
    query.bindValue(":area_muestra", infoMuestra["area_muestra"]);
    query.bindValue(":usuario", infoMuestra["usuario"]);
    query.bindValue(":historia", infoMuestra["historia"]);

    if(infoMuestra.contains("observaciones")){
        query.bindValue(":observaciones", infoMuestra["observaciones"]);
    }

    if(query.exec()){

        id_muestra = query.lastInsertId().toString();

        infoMuestra["id_muestra"] = id_muestra;
        query.clear();
        consulta = "INSERT INTO spectradb.datos_espectrales(muestra";

        int rango = 400;

        for(int i = 0; i < 31; ++i){
            consulta+= ", nm_" + QString().setNum(rango);
            rango+=10;
        }

        consulta+= ") VALUES(:muestra";
        rango = 400;

        for(int i = 0; i < 31; ++i){
            consulta+= ", :nm_" + QString().setNum(rango);
            rango+=10;
        }

        consulta+= ")";
        query.prepare(consulta);
        query.bindValue(":muestra", id_muestra);
        rango = 400;

        for(int i = 0; i < 31; ++i){
            query.bindValue(":nm_" + QString().setNum(rango), datosEspectrales[i]);
            rango+=10;
        }

        if(query.exec()){

            id_datos_espectrales = query.lastInsertId().toString();
            query.clear();
            consulta = "INSERT INTO spectradb.datos_adicionales(datos_espectrales, cie_x, cie_y, cie_z, cie_l, cie_a, cie_b, "
                       "coeficiente_absorcion, coeficiente_esparcimiento, indice_eritema) VALUES(:datos_espectrales, :X, :Y, :Z, "
                       ":L, :A, :B, :absorcion, :esparcimiento, :eritema)";

            query.prepare(consulta);
            query.bindValue(":datos_espectrales", id_datos_espectrales);
            query.bindValue(":X", XYZ[0]);
            query.bindValue(":Y", XYZ[1]);
            query.bindValue(":Z", XYZ[2]);
            query.bindValue(":L", LAB[0]);
            query.bindValue(":A", LAB[1]);
            query.bindValue(":B", LAB[2]);
            query.bindValue(":absorcion", absorcion);
            query.bindValue(":esparcimiento", esparcimiento);
            query.bindValue(":eritema", eritema);

            if(query.exec()){
                QMessageBox::information(this, "Muestra registrada", "Se ha registrado la muestra correctamente.");
                close();
                emit fototipo_registrado(infoMuestra);
            }else{
                qDebug() << query.lastError();
            }
        }else{
            qDebug() << query.lastError();
        }

        consulta = "UPDATE spectradb.historia SET fototipo = '" + QString().setNum(fototipo) + "' WHERE id_historia = '" + id_historia + "'";
        query.prepare(consulta);
        query.exec();
        emit actualizar_fototipo(fototipo);
    }else{
        qDebug() << query.lastError();
        QMessageBox::critical(this, "Error al registrar", "La muestra del fototipo de esta historia ya existe.");
    }
}
