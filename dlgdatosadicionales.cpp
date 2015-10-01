#include "dlgdatosadicionales.h"
#include "ui_dlgdatosadicionales.h"

dlgDatosAdicionales::dlgDatosAdicionales(QVector<float> XYZ, QVector<float> LAB, float eritema, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgDatosAdicionales)
{
    ui->setupUi(this);

    int alto = 37;
    int ancho = 55;

    modeloXYZ = new QStandardItemModel(1, 3, this);

    QStringList cabeceras;

    cabeceras.push_back("x");
    cabeceras.push_back("y");
    cabeceras.push_back("z");
    modeloXYZ->setHorizontalHeaderLabels(cabeceras);
    ui->tablaXYZ->setModel(modeloXYZ);
    ui->tablaXYZ->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tablaXYZ->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tablaXYZ->setRowHeight(0, alto);
    ui->tablaXYZ->setColumnWidth(0, ancho);
    ui->tablaXYZ->setColumnWidth(1, ancho);
    ui->tablaXYZ->setColumnWidth(2, ancho);

    modeloLAB = new QStandardItemModel(1, 3, this);
    cabeceras.clear();
    cabeceras.push_back("L");
    cabeceras.push_back("a");
    cabeceras.push_back("b");
    modeloLAB->setHorizontalHeaderLabels(cabeceras);
    ui->tablaLAB->setModel(modeloLAB);
    ui->tablaLAB->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tablaLAB->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tablaLAB->setRowHeight(0, alto);
    ui->tablaLAB->setColumnWidth(0, ancho);
    ui->tablaLAB->setColumnWidth(1, ancho);
    ui->tablaLAB->setColumnWidth(2, ancho);

    QModelIndex indice;

    for(int i = 0; i < 3; ++i){
        indice = modeloXYZ->index(0, i, QModelIndex());
        modeloXYZ->setData(indice, XYZ.at(i));

        indice = modeloLAB->index(0, i, QModelIndex());
        modeloLAB->setData(indice, LAB.at(i));
    }

    QString auxR;

    auxR.setNum(eritema);
    auxR.replace(".", ",");
    ui->lineaEritema->setText(auxR);

    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}

dlgDatosAdicionales::~dlgDatosAdicionales()
{
    delete ui;
}

void dlgDatosAdicionales::on_btnListo_clicked()
{
    close();
}
