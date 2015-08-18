#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    conectado = false;
    medicion.clear();
    numCurvas = 0;
    fototipo = 0;
    yRef = yAbs = 100;

    modeloPuntos = new QStandardItemModel(2, 31, this);
    QStringList cabeceras;
    cabeceras.push_back("Valor");
    cabeceras.push_back("Longitud");
    modeloPuntos->setVerticalHeaderLabels(cabeceras);
    ui->tablaPuntosEspectrales->setModel(modeloPuntos);
    ui->tablaPuntosEspectrales->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tablaPuntosEspectrales->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    int alto, ancho;
    alto = 45;
    ancho = 55;

    ui->tablaPuntosEspectrales->setRowHeight(0, alto);
    ui->tablaPuntosEspectrales->setRowHeight(1, alto);

    int rango = 400;
    QModelIndex indice;

    for(int i = 0; i < 31; ++i){
        ui->tablaPuntosEspectrales->setColumnWidth(i, ancho);

        indice = modeloPuntos->index(1, i, QModelIndex());
        modeloPuntos->setData(indice, rango);

        rango+=10;
    }

    alto = 37;
    ancho = 55;

    modeloXYZ = new QStandardItemModel(1, 3, this);
    cabeceras.clear();
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

    version = "08162015";
    /*------------------------------------------------------------------------------------------*/
    /*         Creando las curvas de reflectancia difusa y absorbancia aparente                 */
    /*------------------------------------------------------------------------------------------*/
    ref = new dlgGrafica("reflectancia", "Longitud de onda (nm)", "Reflectancia (%)");
    abs = new dlgGrafica("absorbancia", "Longitud de onda (nm)", "Absorbancia (%)");

    revisionBtns();
    this->setFixedSize(this->size());
}

void MainWindow::borrarResultados()
{
    medicion.clear();
    fototipo = 0;

    QModelIndex indice;

    for(int i = 0; i < 31; ++i){
        indice = modeloPuntos->index(0, i, QModelIndex());
        modeloPuntos->setData(indice, "");
    }

    for(int i = 0; i < 3; ++i){
        indice = modeloXYZ->index(0, i, QModelIndex());
        modeloXYZ->setData(indice, "");

        indice = modeloLAB->index(0, i, QModelIndex());
        modeloLAB->setData(indice, "");
    }

    ui->lineaAbsorcion->setText("");
    ui->lineaEsparcimiento->setText("");
    ui->lineaEritema->setText("");

    QSize tam;

    tam.setWidth(125);
    tam.setHeight(125);

    QPixmap imgFototipo(":/img/fototipo_0.png");

    imgFototipo.scaled(tam);
    ui->etqNumeroFototipo->setText("-");
    ui->etqFototipo->setPixmap(imgFototipo);
}

void MainWindow::revisionBtns()
{
    bool btnConectar, btnDesconectar, btnEstandarizar, btnMedir, btnGuardar, btnBorrar,btnFototipo, btnRef, btnAbs;

    if(conectado){
        btnConectar = false;
        btnDesconectar = true;
        btnEstandarizar = btnMedir = true;
    }else{
        btnConectar = true;
        btnDesconectar = false;
         btnEstandarizar = btnMedir = false;
    }

    if(!medicion.isEmpty()){
        btnBorrar = btnFototipo = btnRef = btnAbs = true;

    }else{
        btnBorrar = btnFototipo = btnRef = btnAbs = false;
    }

    if(fototipo != 0){
        btnGuardar = true;
    }else{
        btnGuardar = false;
    }

    ui->actionConectar->setEnabled(btnConectar);
    ui->actionDesconectar->setEnabled(btnDesconectar);
    ui->actionEstandarizar->setEnabled(btnEstandarizar);
    ui->btnMedir->setEnabled(btnMedir);
    ui->btnGuardar->setEnabled(btnGuardar);
    ui->btnBorrar->setEnabled(btnBorrar);
    ui->btnFototipo->setEnabled(btnFototipo);
    ui->btnReflectancia->setEnabled(btnRef);
    ui->btnAbsorbancia->setEnabled(btnAbs);
}

MainWindow::~MainWindow()
{
    if(conectado){
        //miniscan.desconectar();
    }

    delete ui;
}

void MainWindow::on_actionConectar_triggered()
{
    conectado = true;
    //conectado = miniscan.conectar();
    QMessageBox msg;

    if(conectado){
        QMessageBox::information(this, "Conectado", "El MiniScan se ha conectado correctamente");
    }else{
        QMessageBox::critical(this, "Error al conectar", "El MiniScan no se pudo conectar");
    }

    revisionBtns();
}

void MainWindow::on_actionDesconectar_triggered()
{
    conectado = false;
    //conectado = miniscan.desconectar();

    if(!conectado){
        QMessageBox::information(this, "Desconectado", "El MiniScan se ha desconectado correctamente");
    }else{
        QMessageBox::critical(this, "Error al desconectar", "El MiniScan no se pudo desconectar");
    }

    revisionBtns();
}

void MainWindow::on_actionSalir_triggered()
{
    close();
}

void MainWindow::on_btnMedir_clicked()
{
    borrarResultados();

    QVector<double> yRef(31), yAbs(31);
    QVector<float> datosEspectrales(31);

    medicion = miniscan.medir();

    QList<QVariant>::const_iterator iter = qFind(medicion.begin(), medicion.end(), 0);

    if(iter == medicion.end()){
        //si no se consigue ningun cero exacto (0), es porque la lista fue llenada correctamente y por lo tanto la medicion ocurrio

    }else{
        medicion.clear();

        QMessageBox::critical(this, "Error al medir muestra", "La medicion no se pudo realizar");

        medicion.push_back(float(17.2101 + numCurvas));
        medicion.push_back(float(15.2329 + numCurvas));
        medicion.push_back(float(15.13 + numCurvas));
        medicion.push_back(float(14.2457 + numCurvas));
        medicion.push_back(float(16.0641 + numCurvas));
        medicion.push_back(float(18.2752 + numCurvas));
        medicion.push_back(float(19.687 + numCurvas));
        medicion.push_back(float(21.0481 + numCurvas));
        medicion.push_back(float(21.9136 + numCurvas));
        medicion.push_back(float(23.1382 + numCurvas));
        medicion.push_back(float(23.9694 + numCurvas));
        medicion.push_back(float(25.4163 + numCurvas));
        medicion.push_back(float(25.2229 + numCurvas));
        medicion.push_back(float(24.8392 + numCurvas));
        medicion.push_back(float(24.9241 + numCurvas));
        medicion.push_back(float(25.2234 + numCurvas));
        medicion.push_back(float(26.2638 + numCurvas));
        medicion.push_back(float(26.5036 + numCurvas));
        medicion.push_back(float(27.8098 + numCurvas));
        medicion.push_back(float(31.5459 + numCurvas));
        medicion.push_back(float(36.2515 + numCurvas));
        medicion.push_back(float(39.0012 + numCurvas));
        medicion.push_back(float(40.6161 + numCurvas));
        medicion.push_back(float(42.1796 + numCurvas));
        medicion.push_back(float(43.205 + numCurvas));
        medicion.push_back(float(44.057 + numCurvas));
        medicion.push_back(float(45.0165 + numCurvas));
        medicion.push_back(float(45.779 + numCurvas));
        medicion.push_back(float(46.4996 + numCurvas));
        medicion.push_back(float(47.3194 + numCurvas));
        medicion.push_back(float(47.8099 + numCurvas));
    }

    QModelIndex indice;

    for(int i = 0; i < 31; ++i){

        yRef[i] = medicion.at(i).toDouble();
        datosEspectrales[i] = medicion.at(i).toFloat()/100.0;//se dividen los valores entre 100 para obtenerlos en su forma pura
        yAbs[i] = double(100) - medicion.at(i).toDouble();

        indice = modeloPuntos->index(0, i, QModelIndex());
        modeloPuntos->setData(indice, yRef[i]);
    }

    if(ref->numCurvas() > 0){
        ref->quitarCurva();
        abs->quitarCurva();
    }
    ref->agregarCurva(yRef);
    abs->agregarCurva(yAbs);

    QVector<float> XYZ = ops.CIExyz(datosEspectrales);
    QVector<float> LAB = ops.CIELAB(datosEspectrales);
    float absorcion = ops.absorcion(yRef);
    float esparcimiento = ops.esparcimiento(yRef);
    float eritema = ops.eritema(datosEspectrales);

    for(int i = 0; i < 3; ++i){
        indice = modeloXYZ->index(0, i, QModelIndex());
        modeloXYZ->setData(indice, XYZ.at(i));

        indice = modeloLAB->index(0, i, QModelIndex());
        modeloLAB->setData(indice, LAB.at(i));
    }

    QString auxR;

    auxR.setNum(absorcion);
    auxR.replace(".", ",");
    ui->lineaAbsorcion->setText(auxR);
    auxR.setNum(esparcimiento);
    auxR.replace(".", ",");
    ui->lineaEsparcimiento->setText(auxR);
    auxR.setNum(eritema);
    auxR.replace(".", ",");
    ui->lineaEritema->setText(auxR);

    numCurvas += 1;

    revisionBtns();
}

void MainWindow::on_actionAcerca_de_triggered()
{
    QImage logo(":/img/logo_small.png");
    QMessageBox msgBox;
    msgBox.setIconPixmap(QPixmap::fromImage(logo));
    QString titulo("<html><head/><body><p><span style=' font-size:14pt; font-weight:600; color:#4b4b4b;'>Spectrasoft</span>&nbsp; &nbsp;<span style=' font-size:8pt; font-weight:450; color:#4b4b4b;'>versión " + version + "</span></p>");
    QString resumen("<p>Software para el manejo del MiniScan XE Plus.</p>");
    QString desarrollador("<p>Diseñado, desarrollado e implementado por Gabriel Núñez.\nContacto: gabriel.nzn@gmail.com</p></body></html>");
    msgBox.setText(titulo + resumen + desarrollador);
    msgBox.exec();
}

void MainWindow::on_btnFototipo_clicked()
{
    dlgFototipo dlg(ops.fototipo());
    dlg.exec();

    int aux;
    aux = dlg.fototipoSeleccionado();

    if(aux != 0){
        fototipo = aux;
        QSize tam;

        tam.setWidth(125);
        tam.setHeight(125);

        QPixmap imgFototipo(":/img/fototipo_" + QString().setNum(fototipo) + ".png");
        imgFototipo.scaled(tam);

        ui->etqNumeroFototipo->setText(QString().setNum(fototipo));

        ui->etqFototipo->setPixmap(imgFototipo);
    }

    revisionBtns();
}

void MainWindow::on_btnReflectancia_clicked()
{
    ref->exec();
}

void MainWindow::on_btnAbsorbancia_clicked()
{
    abs->exec();
}

void MainWindow::on_actionEstandarizar_triggered()
{
    bool negroListo, blancoListo;
    negroListo = blancoListo = false;
    QMessageBox::information(this, "Prepare la trampa de luz", "Asegurese de tener lista la trampa de luz");
    negroListo = miniscan.estNegro();

    if(negroListo){

        QMessageBox::information(this, "Prepare la cerámica blanca", "Asegurese de tener lista la cerámica blanca");
        blancoListo = miniscan.estBlanco();
    }

    if(negroListo && blancoListo){
        QMessageBox::information(this, "Estandarizado", "El MiniScan se ha estandarizado correctamente");
    }else{
        QMessageBox::critical(this, "Error al estandarizar", "No se pudo estandarizar el MiniScan");
    }

    revisionBtns();
}

void MainWindow::on_btnBorrar_clicked()
{
    borrarResultados();

    revisionBtns();
}
