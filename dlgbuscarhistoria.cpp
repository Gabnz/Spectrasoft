#include "dlgbuscarhistoria.h"
#include "ui_dlgbuscarhistoria.h"

dlgBuscarHistoria::dlgBuscarHistoria(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgBuscarHistoria)
{
    ui->setupUi(this);

    modelo = new QStringListModel(this);
    ui->btnVer->setEnabled(false);
    ui->btnAbrir->setEnabled(false);
    idHistorias.clear();
    infoHistoria.clear();

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

void dlgBuscarHistoria::buscar()
{
    ui->btnAbrir->setEnabled(false);
    ui->btnVer->setEnabled(false);
    infoHistoria.clear();
    idHistorias.clear();
    ui->etqNombre_2->clear();
    ui->etqApellido_2->clear();

    QString consulta, aux;
    QStringList listaHistorias;
    QSqlQuery query;
    int i = 0;
    bool varios = false;

    consulta+= "SELECT id_historia FROM spectradb.historia";

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

        if(ui->checkBoxIFototipo->isChecked()){

            if(varios){
                consulta+= " AND ";
            }else
                varios = true;

            consulta+= "fototipo = '" + ui->cBoxFototipo->currentText() + "'";
        }
    }

    consulta+= " ORDER BY id_historia";

    query.prepare(consulta);
    query.exec();

    while(query.next()){

        listaHistorias.push_back("   Historia " + query.value(0).toString());
        idHistorias[i] = query.value(0).toString();
        ++i;
    }
    modelo->setStringList(listaHistorias);
    ui->listView->setModel(modelo);
}

bool dlgBuscarHistoria::existeCriterio()
{
    return !ui->lineaNombre->text().isEmpty() || !ui->lineaApellido->text().isEmpty() || ui->cBoxSexo->currentIndex() != 0
            || ui->checkBoxICI->isChecked() || ui->checkBoxIFechaNac->isChecked() || ui->checkBoxIFototipo->isChecked();
}

dlgBuscarHistoria::~dlgBuscarHistoria()
{
    delete ui;
}

void dlgBuscarHistoria::on_btnCancelar_clicked()
{
    infoHistoria.clear();
    close();
}


void dlgBuscarHistoria::on_checkBoxICI_toggled(bool checked)
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

void dlgBuscarHistoria::on_checkBoxIFototipo_toggled(bool checked)
{
    if(checked){
        ui->cBoxFototipo->setEnabled(true);
    }else{
        ui->cBoxFototipo->setEnabled(false);
    }
    buscar();
}

void dlgBuscarHistoria::on_checkBoxIFechaNac_toggled(bool checked)
{
    if(checked){
        ui->editFechaNac->setEnabled(true);
    }else{
        ui->editFechaNac->setEnabled(false);
    }
    buscar();
}

void dlgBuscarHistoria::on_lineaNombre_textChanged(const QString &arg1)
{
    ui->lineaNombre->setText(arg1.toUpper());
    buscar();
}

void dlgBuscarHistoria::on_lineaApellido_textChanged(const QString &arg1)
{
    ui->lineaApellido->setText(arg1.toUpper());
    buscar();
}

void dlgBuscarHistoria::on_listView_clicked(const QModelIndex &index)
{
    infoHistoria.clear();
    QSqlQuery query;

    query.exec("SELECT * FROM spectradb.historia WHERE id_historia = '" + idHistorias[index.row()] + "'");

    if(query.next()){

        int indice = query.record().indexOf("id_historia");
        QString aux = query.value(indice).toString();
        infoHistoria["id_historia"] = aux;

        indice = query.record().indexOf("nombre");
        aux = query.value(indice).toString();
        infoHistoria["nombre"] = aux;

        indice = query.record().indexOf("apellido");
        aux = query.value(indice).toString();
        infoHistoria["apellido"] = aux;

        indice = query.record().indexOf("fecha_nac");
        aux = query.value(indice).toString();
        infoHistoria["fecha_nac"] = aux;

        indice = query.record().indexOf("fecha_ingreso");
        aux = query.value(indice).toString();
        infoHistoria["fecha_ingreso"] = aux;

        indice = query.record().indexOf("sexo");
        aux = query.value(indice).toString();
        infoHistoria["sexo"] = aux;

        indice = query.record().indexOf("cedula");
        aux = query.value(indice).toString();

        if(!aux.isEmpty()){
            infoHistoria["cedula"] = aux;
        }

        indice = query.record().indexOf("fototipo");
        aux = query.value(indice).toString();

        if(!aux.isEmpty()){
            infoHistoria["fototipo"] = aux;
        }

        ui->etqNombre_2->setText(infoHistoria["nombre"]);
        ui->etqApellido_2->setText(infoHistoria["apellido"]);

        ui->btnVer->setEnabled(true);
        ui->btnAbrir->setEnabled(true);
    }
}

void dlgBuscarHistoria::on_btnVer_clicked()
{
    dlgVerHistoria verH(infoHistoria);

    verH.exec();
}

void dlgBuscarHistoria::on_cBoxSexo_currentIndexChanged(int index)
{
    buscar();
}

void dlgBuscarHistoria::on_lineaCI_textChanged(const QString &arg1)
{
    buscar();
}

void dlgBuscarHistoria::on_cBoxCI_currentIndexChanged(int index)
{
    buscar();
}

void dlgBuscarHistoria::on_btnAbrir_clicked()
{
    QMessageBox::information(this, "Historia abierta", "Se ha abierto la historia correctamente.");
    close();
    emit historiaAbierta(infoHistoria);
}

void dlgBuscarHistoria::on_editFechaNac_dateChanged(const QDate &date)
{
    buscar();
}

void dlgBuscarHistoria::on_cBoxFototipo_currentIndexChanged(int index)
{
    buscar();
}
