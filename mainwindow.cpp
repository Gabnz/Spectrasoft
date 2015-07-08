#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);
    conectado = false;
    miniscan = new QAxObject;
    miniscan->setControl("MSXEBridge.Bridge");

    //QAxObject *miniscanDirecto = new QAxObject;
    //miniscanDirecto->setControl("MiniScanXE.MSXE");
    //qDebug() << miniscan->dynamicCall("prueba()");
    //miniscan->dynamicCall("Beep()");
    //miniscan->dynamicCall("abrirPuerto()");
    //QVariantList params;
    //miniscanDirecto->dynamicCall("ReadSample(QVariantList*&)", params);
    //miniscan->dynamicCall("medirMuestra()");

    revisionBtns();
    this->adjustSize();
    this->setFixedSize(this->size());
}

void MainWindow::revisionBtns()
{
bool btnConectar, btnDesconectar, btnBeep, btnBlanco, btnNegro, btnMedir;

    if(conectado){
        btnConectar = false;
        btnDesconectar = true;
        btnBeep = btnBlanco = btnNegro = btnMedir = true;
    }else{
        btnConectar = true;
        btnDesconectar = false;
        btnBeep = btnBlanco = btnNegro = btnMedir = false;
    }
    ui->actionConectar->setEnabled(btnConectar);
    ui->actionDesconectar->setEnabled(btnDesconectar);
    ui->btnBeep->setEnabled(btnBeep);
    ui->actionCalibrar_Blanco->setEnabled(btnBlanco);
    ui->actionCalibrar_Negro->setEnabled(btnNegro);
    ui->btnMedir->setEnabled(btnMedir);
}

MainWindow::~MainWindow()
{
    if(conectado)
        ui->actionDesconectar->trigger();

    delete ui;
}

void MainWindow::on_actionConectar_triggered(){

    QVariant resultado;
    resultado = miniscan->dynamicCall("abrirPuerto()");
    conectado = resultado.toBool();
    revisionBtns();
}

void MainWindow::on_actionDesconectar_triggered()
{
    miniscan->dynamicCall("cerrarPuerto()");
    revisionBtns();
}

void MainWindow::on_actionSalir_triggered()
{
    close();
}

void MainWindow::on_actionCalibrar_Blanco_triggered()
{
    miniscan->dynamicCall("medirBlanco()");
    revisionBtns();
}

void MainWindow::on_actionCalibrar_Negro_triggered()
{
    miniscan->dynamicCall("medirNegro()");
    revisionBtns();
}

void MainWindow::on_btnMedir_clicked()
{
    miniscan->dynamicCall("medirMuestra()");
    revisionBtns();
}

void MainWindow::on_btnBeep_clicked()
{
    miniscan->dynamicCall("Beep()");
    revisionBtns();
}
