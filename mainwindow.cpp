#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    conectado = false;
    miniscan = new QAxObject;

    //si se puede usar el .dll sin registrar, pero hace falta determinar que estructura debe tener el .dll en vb.net para poderse usar de esa forma
    //miniscan->setControl("D:/Code/Qt-projects/MiniscanXE/MSXEBridge.dll");

    miniscan->setControl("MSXE.Bridge");

    this->adjustSize();
    //this->setFixedSize(this->size());
    revisionBtns();
}

void MainWindow::revisionBtns()
{
    bool btnConectar, btnDesconectar, btnBlanco, btnNegro, btnMedir;

    if(conectado){
        btnConectar = false;
        btnDesconectar = true;
        btnBlanco = btnNegro = btnMedir = true;
    }else{
        btnConectar = true;
        btnDesconectar = false;
        btnBlanco = btnNegro = btnMedir = false;
    }
    ui->actionConectar->setEnabled(btnConectar);
    ui->actionDesconectar->setEnabled(btnDesconectar);
    ui->actionCalibrar_Blanco->setEnabled(btnBlanco);
    ui->actionCalibrar_Negro->setEnabled(btnNegro);
    ui->btnMedir->setEnabled(btnMedir);
}

MainWindow::~MainWindow()
{
    if(conectado)
        miniscan->dynamicCall("cerrarPuerto()");

    delete ui;
}

void MainWindow::on_actionConectar_triggered()
{
    conectado = miniscan->dynamicCall("abrirPuerto()").toBool();

    if(conectado){
        miniscan->dynamicCall("Beep()");
        QMessageBox::information(this, "Dispositivo conectado", "El dispositivo ha sido conectado correctamente");
    }else{
        QMessageBox::critical(this, "Error al conectar", "El dispositivo no se pudo conectar");
    }

    revisionBtns();
}

void MainWindow::on_actionDesconectar_triggered()
{
    conectado = !(miniscan->dynamicCall("cerrarPuerto()").toBool());

    if(!conectado){
        QMessageBox::information(this, "Dispositivo desconectado", "El dispositivo ha sido desconectado correctamente");
    }else{
        QMessageBox::critical(this, "Error al desconectar", "El dispositivo no se pudo desconectar");
    }

    revisionBtns();
}

void MainWindow::on_actionSalir_triggered()
{
    close();
}

void MainWindow::on_actionCalibrar_Blanco_triggered()
{
    bool calibrado;

    calibrado = miniscan->dynamicCall("leerBlanco()").toBool();

    if(calibrado){
        QMessageBox::information(this, "Blanco calibrado", "El color blanco ha sido calibrado correctamente");
    }else{
        QMessageBox::critical(this, "Error al calibrar blanco", "El color blanco no se pudo calibrar");
    }

    revisionBtns();
}

void MainWindow::on_actionCalibrar_Negro_triggered()
{
    bool calibrado;

    calibrado = miniscan->dynamicCall("leerNegro()").toBool();

    if(calibrado){
        QMessageBox::information(this, "Negro calibrado", "El color negro ha sido calibrado correctamente");
    }else{
        QMessageBox::critical(this, "Error al calibrar negro", "El color negro no se pudo calibrar");
    }

    revisionBtns();
}

void MainWindow::on_btnMedir_clicked()
{
    QVariant resultado;
    QList<QVariant> medicion;
    QVector<double> x(31), y(31);
    int yMax;
    double yAux;

    resultado = miniscan->dynamicCall("medirMuestra()");
    qDebug() << resultado << endl;
    medicion = resultado.toList();

    if(medicion.size() == 0){

        QMessageBox::critical(this, "Error al medir muestra", "La medicion no se pudo realizar");

        medicion.push_back(0.01);
        medicion.push_back(3.982208);
        medicion.push_back(3.954711);
        medicion.push_back(3.675615);
        medicion.push_back(4.137294);
        medicion.push_back(3.721477);
        medicion.push_back(3.569634);
        medicion.push_back(3.721159);
        medicion.push_back(3.829374);
        medicion.push_back(3.684407);
        medicion.push_back(3.880684);
        medicion.push_back(3.8164);
        medicion.push_back(3.707666);
        medicion.push_back(3.882417);
        medicion.push_back(3.799666);
        medicion.push_back(3.756054);
        medicion.push_back(3.57211);
        medicion.push_back(3.671774);
        medicion.push_back(3.539208);
        medicion.push_back(3.605787);
        medicion.push_back(3.711717);
        medicion.push_back(3.673021);
        medicion.push_back(3.467857);
        medicion.push_back(4.030558);
        medicion.push_back(3.721215);
        medicion.push_back(4.220217);
        medicion.push_back(5.147172);
        medicion.push_back(6.31108);
        medicion.push_back(10.0476);
        medicion.push_back(13.53243);
        medicion.push_back(17.15057);
    }

    yAux = 0;
    int j = 400;

    for(int i = 0; i < 31; ++i){
        x[i] = j;
        y[i] = medicion.at(i).toDouble();

        if(medicion.at(i).toDouble() > yAux){
            yAux = medicion.at(i).toDouble();
        }
        j+=10;
    }

    yMax = static_cast<int>(yAux);

    ui->plotReflectancia->addGraph();
    ui->plotReflectancia->graph(0)->setData(x, y);
    ui->plotReflectancia->xAxis->setRange(400, 700);
    ui->plotReflectancia->yAxis->setRange(0, yMax);
    ui->plotReflectancia->xAxis->setLabel("Nanometros");
    ui->plotReflectancia->yAxis->setLabel("Eje Y");
    //ui->plotReflectancia->setInteraction(QCP::iRangeDrag, true);
    //ui->plotReflectancia->setInteraction(QCP::iRangeZoom, true);
    ui->plotReflectancia->replot();

    revisionBtns();
}
