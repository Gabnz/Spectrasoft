#include "dlgreghistoria.h"
#include "ui_dlgreghistoria.h"

dlgRegHistoria::dlgRegHistoria(QString claveUsuario, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgRegHistoria)
{
    ui->setupUi(this);

    infoHistoria.clear();
    clave = claveUsuario;
    nombreListo = apellidoListo = sexoListo = false;
    cedulaLista = fecha_nacLista = true;
    ui->btnRegistrar->setEnabled(false);

    QRegExp rx("^([a-zA-Z]+([ ]?[a-zA-Z]?[a-zA-Z]+)*)$");
    QValidator *soloPalabras = new QRegExpValidator(rx, this);
    ui->lineaNombre->setValidator(soloPalabras);
    ui->lineaApellido->setValidator(soloPalabras);

    QValidator *soloNumeros = new QIntValidator(1, 999999999, this);
    ui->lineaCI->setValidator(soloNumeros);

    QDate fechaMinima, fechaDefecto;
    fechaMinima = fechaDefecto = QDate::currentDate();
    fechaMinima.setDate(fechaMinima.year() - 120,fechaMinima.month(), fechaMinima.day() );
    fechaDefecto.setDate(fechaDefecto.year() - 18, fechaMinima.month(), fechaMinima.day());
    ui->editFechaNac->setDate(fechaDefecto);
    ui->editFechaNac->setDateRange(fechaMinima, QDate::currentDate());

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

bool dlgRegHistoria::camposListos()
{
    return nombreListo && apellidoListo && cedulaLista && fecha_nacLista && sexoListo;
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
    ui->lineaNombre->setText(arg1.toUpper());

    if(ui->lineaNombre->text().length() >= 3){
        nombreListo = true;
    }else{
        nombreListo = false;
    }

    if(camposListos())
        ui->btnRegistrar->setEnabled(true);
    else
        ui->btnRegistrar->setEnabled(false);
}

void dlgRegHistoria::on_lineaApellido_textChanged(const QString &arg1)
{
    ui->lineaApellido->setText(arg1.toUpper());

    if(ui->lineaApellido->text().length() >= 3){
        apellidoListo = true;
    }else{
        apellidoListo = false;
    }

    if(camposListos())
        ui->btnRegistrar->setEnabled(true);
    else
        ui->btnRegistrar->setEnabled(false);
}

void dlgRegHistoria::on_cBoxSexo_currentIndexChanged(int index)
{
    if(index != 0){
        sexoListo = true;
    }else{
        sexoListo = false;
    }

    if(camposListos())
        ui->btnRegistrar->setEnabled(true);
    else
        ui->btnRegistrar->setEnabled(false);
}

void dlgRegHistoria::on_btnRegistrar_clicked()
{
    dlgConfirmarClave confirmar(clave);

    connect(&confirmar, &dlgConfirmarClave::claveIntroducida, this, &dlgRegHistoria::on_claveIntroducida);

    confirmar.exec();
}

void dlgRegHistoria::on_claveIntroducida(bool correcta)
{
    if(correcta){
        infoHistoria["nombre"] = ui->lineaNombre->text();
        infoHistoria["apellido"] = ui->lineaApellido->text();
        infoHistoria["fecha_nac"] = ui->editFechaNac->date().toString("yyyy-MM-dd");
        infoHistoria["fecha_ingreso"] = QDate::currentDate().toString("yyyy-MM-dd");

        if(ui->cBoxSexo->currentIndex() == 1)
            infoHistoria["sexo"] = "F";
        else
            infoHistoria["sexo"] = "M";

        if(!ui->lineaCI->text().isEmpty()){
            infoHistoria["cedula"] = ui->cBoxCI->currentText() + ui->lineaCI->text();
        }

        QString consulta;

        consulta = "INSERT INTO spectradb.historia(nombre, apellido, fecha_nac, fecha_ingreso, sexo";

        if(infoHistoria.contains("cedula")){
            consulta+= ", cedula";
        }

        consulta += ") VALUES(:nombre, :apellido, :fecha_nac, :fecha_ingreso, :sexo";

        if(infoHistoria.contains("cedula")){
            consulta+= ", :cedula";
        }

        consulta += ")";

        QSqlQuery query;

        query.prepare(consulta);

        query.bindValue(":nombre", infoHistoria["nombre"]);
        query.bindValue(":apellido", infoHistoria["apellido"]);
        query.bindValue(":fecha_nac", infoHistoria["fecha_nac"]);
        query.bindValue(":fecha_ingreso", infoHistoria["fecha_ingreso"]);
        query.bindValue(":sexo", infoHistoria["sexo"]);

        if(infoHistoria.contains("cedula")){
            query.bindValue(":cedula", infoHistoria["cedula"]);
        }

        if(query.exec()){
            infoHistoria["id_historia"] = query.lastInsertId().toString();

            QMessageBox::information(this, "Historia registrada", "Se ha registrado la historia correctamente.");
            close();
            emit historia_registrada(infoHistoria);
        }else{
            //el codigo 23505 significa que se intento insertar un valor unico que ya existe
            if(query.lastError().number() == 23505){
                QMessageBox::critical(this, "Error al registrar", "La cédula de identidad " + infoHistoria["cedula"] + " ya está siendo utilizada.");
            }

            infoHistoria.clear();
            ui->lineaCI->clear();
        }
    }else{
        QMessageBox::critical(this, "Contraseña incorrecta", "La contraseña que introdujo es incorrecta.");
    }
}
