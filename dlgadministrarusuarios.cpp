#include "dlgadministrarusuarios.h"
#include "ui_dlgadministrarusuarios.h"

dlgAdministrarUsuarios::dlgAdministrarUsuarios(QString cedulaUsuario, QString claveUsuario, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgAdministrarUsuarios)
{
    ui->setupUi(this);

    cedula = cedulaUsuario;
    clave = claveUsuario;
    modelo = new QStringListModel(this);

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

    buscar();

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

void dlgAdministrarUsuarios::revisionBtns()
{
    if(!infoUsuario.isEmpty()){

        ui->btnVer->setEnabled(true);
        ui->btnRol->setEnabled(true);

        if(infoUsuario["rol"] != "administrador"){
            ui->btnClave->setEnabled(true);
            ui->btnEliminar->setEnabled(true);
        }else{
            ui->btnClave->setEnabled(false);
            ui->btnEliminar->setEnabled(false);
        }

    }else{
        ui->btnVer->setEnabled(false);
        ui->btnRol->setEnabled(false);
        ui->btnClave->setEnabled(false);
        ui->btnEliminar->setEnabled(false);
    }
}

void dlgAdministrarUsuarios::buscar()
{
    infoUsuario.clear();
    ciUsuarios.clear();
    ui->etqNombre_2->clear();
    ui->etqApellido_2->clear();

    QString consulta, aux;
    QStringList listaUsuarios;
    QSqlQuery query;
    int i = 0;
    bool varios = false;

    consulta = "SELECT cedula FROM spectradb.usuario";

    if(existeCriterio()){
        consulta+= " WHERE ";

        if(!ui->lineaNombre->text().isEmpty()){
            consulta+= "nombre LIKE '%" + ui->lineaNombre->text() + "%'";
            varios = true;
        }

        if(!ui->lineaApellido->text().isEmpty()){

            if(varios){
                consulta += " AND ";
            }else
                varios = true;

            consulta+= "apellido LIKE '%" + ui->lineaApellido->text() + "%'";
        }

        if(ui->cBoxSexo->currentIndex() != 0){

            if(varios){
                consulta+= " AND ";
            }else
                varios = true;

            if(ui->cBoxSexo->currentIndex() == 1){
                aux = "F";
            }else{
                aux = "M";
            }
            consulta+= "sexo = '" + aux + "'";
        }

        if(ui->cBoxRol->currentIndex() != 0){

            if(varios){
                consulta+= " AND ";
            }else
                varios = true;

            if(ui->cBoxRol->currentIndex() == 1){
                aux = "administrador";
            }else if(ui->cBoxRol->currentIndex() == 2){
                aux = "dermatologo";
            }else{
                aux = "investigador";
            }
            consulta+= "rol = '" + aux + "'";
        }

        if(ui->checkBoxICI->isChecked()){

            if(varios){
                consulta+= " AND ";
            }else
                varios = true;

            consulta+= "cedula LIKE '%" + ui->cBoxCI->currentText() + ui->lineaCI->text() + "%'";
        }

        if(ui->checkBoxIFechaNac->isChecked()){

            if(varios){
                consulta+= " AND ";
            }else
                varios = true;

            consulta+= "fecha_nac = '%" + ui->editFechaNac->date().toString("yyyy-MM-dd") + "%'";
        }
    }

    if(existeCriterio() && varios){
        consulta+= " AND ";
    }else{
        consulta+= " WHERE ";
    }

    consulta+= "cedula != '" + cedula + "' ORDER BY cedula";
    query.prepare(consulta);
    query.exec();

    while(query.next()){

        listaUsuarios.push_back("   Usuario " + query.value(0).toString());
        ciUsuarios[i] = query.value(0).toString();
        ++i;
    }
    modelo->setStringList(listaUsuarios);
    ui->listView->setModel(modelo);

    revisionBtns();
}

bool dlgAdministrarUsuarios::existeCriterio()
{
    return !ui->lineaNombre->text().isEmpty() || !ui->lineaApellido->text().isEmpty() || ui->cBoxSexo->currentIndex() != 0
            || ui->cBoxRol->currentIndex() != 0 || ui->checkBoxICI->isChecked() || ui->checkBoxIFechaNac->isChecked();
}

dlgAdministrarUsuarios::~dlgAdministrarUsuarios()
{
    delete ui;
}

void dlgAdministrarUsuarios::on_btnCancelar_clicked()
{
    close();
}

void dlgAdministrarUsuarios::on_lineaNombre_textChanged(const QString &arg1)
{
    ui->lineaNombre->setText(arg1.toUpper());
    buscar();
}

void dlgAdministrarUsuarios::on_lineaApellido_textChanged(const QString &arg1)
{
    ui->lineaApellido->setText(arg1.toUpper());
    buscar();
}

void dlgAdministrarUsuarios::on_cBoxSexo_currentIndexChanged(int index)
{
    buscar();
}

void dlgAdministrarUsuarios::on_cBoxRol_currentIndexChanged(int index)
{
    buscar();
}

void dlgAdministrarUsuarios::on_checkBoxICI_toggled(bool checked)
{
    if(checked){
        ui->cBoxCI->setEnabled(true);
        ui->lineaCI->setEnabled(true);
    }else{
        ui->cBoxCI->setEnabled(false);
        ui->lineaCI->setEnabled(false);
        ui->cBoxCI->setCurrentIndex(0);
        ui->lineaCI->clear();
    }
    buscar();
}

void dlgAdministrarUsuarios::on_checkBoxIFechaNac_toggled(bool checked)
{
    if(checked){
        ui->editFechaNac->setEnabled(true);
    }else{
        ui->editFechaNac->setEnabled(false);
    }
    buscar();
}

void dlgAdministrarUsuarios::on_cBoxCI_currentIndexChanged(int index)
{
    buscar();
}

void dlgAdministrarUsuarios::on_lineaCI_textChanged(const QString &arg1)
{
    buscar();
}

void dlgAdministrarUsuarios::on_editFechaNac_dateChanged(const QDate &date)
{
    buscar();
}

void dlgAdministrarUsuarios::on_btnVer_clicked()
{
    dlgVerUsuario verU(infoUsuario);
    verU.exec();
}

void dlgAdministrarUsuarios::on_listView_clicked(const QModelIndex &index)
{
    infoUsuario.clear();
    QSqlQuery query;

    query.exec("SELECT * FROM spectradb.usuario WHERE cedula = '" + ciUsuarios[index.row()] + "'");

    if(query.next()){

        int indice = query.record().indexOf("cedula");
        QString aux = query.value(indice).toString();
        infoUsuario["cedula"] = aux;

        indice = query.record().indexOf("rol");
        aux = query.value(indice).toString();
        infoUsuario["rol"] = aux;

        indice = query.record().indexOf("nombre");
        aux = query.value(indice).toString();
        infoUsuario["nombre"] = aux;

        indice = query.record().indexOf("apellido");
        aux = query.value(indice).toString();
        infoUsuario["apellido"] = aux;

        indice = query.record().indexOf("fecha_nac");
        aux = query.value(indice).toString();
        infoUsuario["fecha_nac"] = aux;

        indice = query.record().indexOf("sexo");
        aux = query.value(indice).toString();
        infoUsuario["sexo"] = aux;

        ui->etqNombre_2->setText(infoUsuario["nombre"]);
        ui->etqApellido_2->setText(infoUsuario["apellido"]);

        revisionBtns();
    }
}

void dlgAdministrarUsuarios::on_btnRol_clicked()
{
    dlgCambiarRol cambiarRol(infoUsuario["cedula"], clave, infoUsuario["rol"]);

    connect(&cambiarRol, &dlgCambiarRol::rolCambiado, this, &dlgAdministrarUsuarios::on_rolCambiado);
    cambiarRol.exec();
}

void dlgAdministrarUsuarios::on_rolCambiado(QString rol)
{
    infoUsuario["rol"] = rol;
    revisionBtns();
}
