#include "dlgregusuario.h"
#include "ui_dlgregusuario.h"

dlgRegUsuario::dlgRegUsuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgRegUsuario)
{
    ui->setupUi(this);

    infoUsuario.clear();
    nombreListo = apellidoListo = cedulaLista = rolListo = claveLista = sexoListo = false;
    fecha_nacLista = true;
    ui->btnRegistrar->setEnabled(false);

    QRegExp rx("^([a-zA-Z]+([ ]?[a-zA-Z]?[a-zA-Z]+)*)$");
    QValidator *soloPalabras = new QRegExpValidator(rx, this);
    ui->lineaNombre->setValidator(soloPalabras);
    ui->lineaApellido->setValidator(soloPalabras);

    claveValida.setPattern("^((?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).{8,16})$");

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

bool dlgRegUsuario::camposListos()
{
    return nombreListo && apellidoListo && cedulaLista && rolListo && claveLista && fecha_nacLista && sexoListo;
}

dlgRegUsuario::~dlgRegUsuario()
{
    delete ui;
}

void dlgRegUsuario::on_btnCancelar_clicked()
{
    close();
}

void dlgRegUsuario::on_lineaNombre_textChanged(const QString &arg1)
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

void dlgRegUsuario::on_lineaApellido_textChanged(const QString &arg1)
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

void dlgRegUsuario::on_lineaCI_textChanged(const QString &arg1)
{
    if(arg1.length() >= 1){
        cedulaLista = true;
    }else{
        cedulaLista = false;
    }

    if(camposListos())
        ui->btnRegistrar->setEnabled(true);
    else
        ui->btnRegistrar->setEnabled(false);
}

void dlgRegUsuario::on_cBoxRol_currentIndexChanged(int index)
{
    if(index != 0){
        rolListo = true;
    }else{
        rolListo = false;
    }

    if(camposListos())
        ui->btnRegistrar->setEnabled(true);
    else
        ui->btnRegistrar->setEnabled(false);
}

void dlgRegUsuario::on_lineaClave_textChanged(const QString &arg1)
{
    QRegularExpressionMatch claveMatch = claveValida.match(arg1);

    if(claveMatch.hasMatch()){
        ui->etqClaveValida->setPixmap(QPixmap::fromImage(QImage(":/img/correcto.png")));

        if(!ui->lineaRepetirClave->text().isEmpty() && ui->lineaRepetirClave->text() == arg1){
            ui->etqClaveRepetidaValida->setPixmap(QPixmap::fromImage(QImage(":/img/correcto.png")));
            claveLista = true;
        }else{
            ui->etqClaveRepetidaValida->setPixmap(QPixmap::fromImage(QImage(":/img/incorrecto.png")));
            claveLista = false;
        }

    }else{
        ui->etqClaveValida->setPixmap(QPixmap::fromImage(QImage(":/img/incorrecto.png")));

        if(!ui->lineaRepetirClave->text().isEmpty()){
            ui->etqClaveRepetidaValida->setPixmap(QPixmap::fromImage(QImage(":/img/incorrecto.png")));
        }

        claveLista = false;
    }

    if(camposListos())
        ui->btnRegistrar->setEnabled(true);
    else
        ui->btnRegistrar->setEnabled(false);
}

void dlgRegUsuario::on_lineaRepetirClave_textChanged(const QString &arg1)
{
     QRegularExpressionMatch claveMatch = claveValida.match(arg1);

    if(arg1 == ui->lineaClave->text() && claveMatch.hasMatch()){
        ui->etqClaveRepetidaValida->setPixmap(QPixmap::fromImage(QImage(":/img/correcto.png")));
        claveLista = true;
    }else{
        claveLista = false;
        ui->etqClaveRepetidaValida->setPixmap(QPixmap::fromImage(QImage(":/img/incorrecto.png")));
    }

    if(camposListos())
        ui->btnRegistrar->setEnabled(true);
    else
        ui->btnRegistrar->setEnabled(false);
}

void dlgRegUsuario::on_cBoxSexo_currentIndexChanged(int index)
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

void dlgRegUsuario::on_btnRegistrar_clicked()
{
    infoUsuario["cedula"] = ui->cBoxCI->currentText() + ui->lineaCI->text();
    infoUsuario["nombre"] = ui->lineaNombre->text();
    infoUsuario["apellido"] = ui->lineaApellido->text();
    infoUsuario["fecha_nac"] = ui->editFechaNac->date().toString("yyyy-MM-dd");
    infoUsuario["clave"] = ui->lineaClave->text();

    if(ui->cBoxRol->currentIndex() == 1)
        infoUsuario["rol"] = "dermatologo";
    else if(ui->cBoxRol->currentIndex() == 2)
        infoUsuario["rol"] = "investigador";
    else
        infoUsuario["rol"] = "administrador";

    if(ui->cBoxSexo->currentIndex() == 1)
        infoUsuario["sexo"] = "F";
    else
        infoUsuario["sexo"] = "M";

    QSqlQuery query;

    query.prepare("INSERT INTO spectradb.usuario(cedula, nombre, apellido, fecha_nac, sexo, clave, rol)"
                  " VALUES(:cedula, :nombre, :apellido, :fecha_nac, :sexo, :clave, :rol)");

    query.bindValue(":cedula", infoUsuario["cedula"]);
    query.bindValue(":nombre", infoUsuario["nombre"]);
    query.bindValue(":apellido", infoUsuario["apellido"]);
    query.bindValue(":fecha_nac", infoUsuario["fecha_nac"]);
    query.bindValue(":sexo", infoUsuario["sexo"]);
    query.bindValue(":clave", infoUsuario["clave"]);
    query.bindValue(":rol", infoUsuario["rol"]);

    if(query.exec()){
        QMessageBox::information(this, "Usuario registrado", "Se ha registrado el usuario correctamente.");
        close();
    }else{
        //el codigo 23505 significa que se intento insertar un valor unico que ya existe
        if(query.lastError().number() == 23505){
            QMessageBox::critical(this, "Error al registrar", "La cédula de identidad " + infoUsuario["cedula"] + " ya está siendo utilizada.");
        }

        infoUsuario.clear();
        ui->lineaClave->clear();
        ui->lineaRepetirClave->clear();
        ui->etqClaveValida->setPixmap(QPixmap::fromImage(QImage(":/img/vacio.png")));
        ui->etqClaveRepetidaValida->setPixmap(QPixmap::fromImage(QImage(":/img/vacio.png")));
        ui->btnRegistrar->setEnabled(false);
    }
}
