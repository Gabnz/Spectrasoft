#include "dlgbuscarmuestra.h"
#include "ui_dlgbuscarmuestra.h"

dlgBuscarMuestra::dlgBuscarMuestra(QString idHistoria, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgBuscarMuestra)
{
    ui->setupUi(this);

    historia = idHistoria;
    modelo = new QStringListModel(this);
    ui->btnVer->setEnabled(false);
    ui->btnAbrir->setEnabled(false);
    idMuestras.clear();
    infoMuestra.clear();

    QRegExp rx("^([a-zA-Z]+([ ]?[a-zA-Z]?[a-zA-Z]+)*)$");
    QValidator *soloPalabras = new QRegExpValidator(rx, this);
    ui->lineaNombre->setValidator(soloPalabras);
    ui->lineaArea->setValidator(soloPalabras);
    ui->editFechaM->setMaximumDate(QDate::currentDate());

    buscar();

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

void dlgBuscarMuestra::buscar()
{
    ui->btnAbrir->setEnabled(false);
    ui->btnVer->setEnabled(false);
    infoMuestra.clear();
    idMuestras.clear();
    ui->etqNombre_2->clear();
    ui->etqArea_2->clear();

    QString consulta, aux;
    QStringList listaMuestras;
    QSqlQuery query;
    int i = 0;

    consulta+= "SELECT id_muestra FROM spectradb.muestra WHERE historia = '" + historia + "'";

    if(existeCriterio()){

        if(!ui->lineaNombre->text().isEmpty()){
            consulta+= " AND nombre_muestra LIKE '%" + ui->lineaNombre->text() + "%'";
        }

        if(!ui->lineaArea->text().isEmpty()){
            consulta+= " AND area_muestra LIKE '%" + ui->lineaArea->text() + "%'";
        }

        if(ui->cBoxTipo->currentIndex() != 0){

            if(ui->cBoxTipo->currentIndex() == 1){
                aux = "fototipo";
            }else{
                aux = "lesion";
            }
            consulta+= " AND tipo_muestra = '" + aux + "'";
        }

        if(ui->checkBoxIFechaM->isChecked()){
            consulta+= " AND fecha_muestra = '%" + ui->editFechaM->date().toString("yyyy-MM-dd") + "%'";
        }
    }
    consulta+= "ORDER BY tipo_muestra";

    query.prepare(consulta);
    query.exec();

    while(query.next()){

        listaMuestras.push_back("   Muestra " + query.value(0).toString());
        idMuestras[i] = query.value(0).toString();
        ++i;
    }
    modelo->setStringList(listaMuestras);
    ui->listView->setModel(modelo);
}

bool dlgBuscarMuestra::existeCriterio()
{
    return !ui->lineaNombre->text().isEmpty() || !ui->lineaArea->text().isEmpty() || ui->cBoxTipo->currentIndex() != 0 || ui->checkBoxIFechaM->isChecked();
}

dlgBuscarMuestra::~dlgBuscarMuestra()
{
    delete ui;
}

void dlgBuscarMuestra::on_cBoxTipo_currentIndexChanged(int index)
{
    buscar();
}

void dlgBuscarMuestra::on_lineaNombre_textChanged(const QString &arg1)
{
    ui->lineaNombre->setText(arg1.toUpper());
    buscar();
}

void dlgBuscarMuestra::on_lineaArea_textChanged(const QString &arg1)
{
    ui->lineaArea->setText(arg1.toUpper());
    buscar();
}

void dlgBuscarMuestra::on_checkBoxIFechaM_toggled(bool checked)
{
    if(checked){
        ui->editFechaM->setEnabled(true);
    }else{
        ui->editFechaM->setEnabled(false);
    }
    buscar();
}

void dlgBuscarMuestra::on_listView_clicked(const QModelIndex &index)
{
    infoMuestra.clear();
    QSqlQuery query;

    query.exec("SELECT * FROM spectradb.muestra WHERE id_muestra = '" + idMuestras[index.row()] + "'");

    if(query.next()){

        int indice = query.record().indexOf("id_muestra");
        QString aux = query.value(indice).toString();
        infoMuestra["id_muestra"] = aux;

        indice = query.record().indexOf("usuario");
        aux = query.value(indice).toString();
        infoMuestra["usuario"] = aux;

        indice = query.record().indexOf("historia");
        aux = query.value(indice).toString();
        infoMuestra["historia"] = aux;

        indice = query.record().indexOf("datos_espectrales");
        aux = query.value(indice).toString();
        infoMuestra["datos_espectrales"] = aux;

        indice = query.record().indexOf("tipo_muestra");
        aux = query.value(indice).toString();
        infoMuestra["tipo_muestra"] = aux;

        indice = query.record().indexOf("nombre_muestra");
        aux = query.value(indice).toString();
        infoMuestra["nombre_muestra"] = aux;

        indice = query.record().indexOf("area_muestra");
        aux = query.value(indice).toString();
        infoMuestra["area_muestra"] = aux;

        indice = query.record().indexOf("fecha_muestra");
        aux = query.value(indice).toString();
        infoMuestra["fecha_muestra"] = aux;

        indice = query.record().indexOf("observaciones");
        aux = query.value(indice).toString();

        if(!aux.isEmpty()){
            infoMuestra["observaciones"] = aux;
        }

        ui->etqNombre_2->setText(infoMuestra["nombre_muestra"]);
        ui->etqArea_2->setText(infoMuestra["area_muestra"]);

        ui->btnVer->setEnabled(true);
        ui->btnAbrir->setEnabled(true);
    }
}

void dlgBuscarMuestra::on_btnVer_clicked()
{
    dlgVerMuestra verM(infoMuestra);

    verM.exec();
}

void dlgBuscarMuestra::on_btnAbrir_clicked()
{
    QSqlQuery query;
    QString id_datos_espectrales;
    QVector<float> datosE, XYZ, LAB, adicionales;
    int i, indice;

    query.exec("SELECT * FROM spectradb.datos_espectrales WHERE id_datos_espectrales = '" + infoMuestra["datos_espectrales"] + "'");

    query.next();

    int rango = 400;

    for(i = 0; i < 31; ++i){
        indice = query.record().indexOf("nm_" + QString().setNum(rango));
        datosE.push_back(query.value(indice).toFloat());
        rango+=10;
    }
    indice = query.record().indexOf("id_datos_espectrales");
    id_datos_espectrales = query.value(indice).toString();

    query.exec("SELECT * FROM spectradb.datos_adicionales WHERE datos_espectrales = '" + id_datos_espectrales + "'");

    query.next();

    indice = query.record().indexOf("cie_x");
    XYZ.push_back(query.value(indice).toFloat());
    indice = query.record().indexOf("cie_y");
    XYZ.push_back(query.value(indice).toFloat());
    indice = query.record().indexOf("cie_z");
    XYZ.push_back(query.value(indice).toFloat());

    indice = query.record().indexOf("cie_l");
    LAB.push_back(query.value(indice).toFloat());
    indice = query.record().indexOf("cie_a");
    LAB.push_back(query.value(indice).toFloat());
    indice = query.record().indexOf("cie_b");
    LAB.push_back(query.value(indice).toFloat());

    indice = query.record().indexOf("coeficiente_absorcion");
    adicionales.push_back(query.value(indice).toFloat());
    indice = query.record().indexOf("coeficiente_esparcimiento");
    adicionales.push_back(query.value(indice).toFloat());
    indice = query.record().indexOf("indice_eritema");
    adicionales.push_back(query.value(indice).toFloat());

    QMessageBox::information(this, "Muestra abierta", "Se ha abierto la muestra correctamente.");
    close();
    emit muestraAbierta(infoMuestra, datosE, XYZ, LAB, adicionales);
}

void dlgBuscarMuestra::on_btnCancelar_clicked()
{
    close();
}

void dlgBuscarMuestra::on_editFechaM_dateChanged(const QDate &date)
{
    buscar();
}
