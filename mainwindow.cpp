#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    conectado = false;
    numCurvas = 0;
    yRef = yAbs = 100;
    modelo = new QStandardItemModel(2, 31, this);
    QStringList cabeceras;
    cabeceras.push_back("Valor");
    cabeceras.push_back("Longitud");
    modelo->setVerticalHeaderLabels(cabeceras);
    ui->tablaPuntosEspectrales->setModel(modelo);
    version = "08122015";
    /*------------------------------------------------------------------------------------------*/
    /*         Creando la curva de reflectancia difusa y la curva de absorbancia aparente       */
    /*------------------------------------------------------------------------------------------*/
    reflectancia = new Grafica(ui->graficaReflectancia, this, "Curva de reflectancia difusa", "Longitud de onda (nm)", "Reflectancia (%)");
    absorbancia = new Grafica(ui->graficaAbsorbancia, this, "Curva de absorbancia aparente", "Longitud de onda (nm)", "Absorbancia (%)");

    connect(ui->graficaReflectancia->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(ajustarRefX(QCPRange)));
    connect(ui->graficaReflectancia->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(ajustarRefY(QCPRange)));
    connect(ui->graficaAbsorbancia->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(ajustarAbsX(QCPRange)));
    connect(ui->graficaAbsorbancia->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(ajustarAbsY(QCPRange)));

    ui->refSpinY->setValue(yRef);
    ui->absSpinY->setValue(yAbs);

    revisionBtns();
    this->adjustSize();
    this->setFixedSize(this->size());
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
    ui->actionEstandarizar_Blanco->setEnabled(btnBlanco);
    ui->actionEstandarizar_Negro->setEnabled(btnNegro);
    //ui->btnMedir->setEnabled(btnMedir);
}

MainWindow::~MainWindow()
{
    if(conectado){
        miniscan.desconectar();
    }

    delete ui;
}

void MainWindow::on_actionConectar_triggered()
{
    conectado = miniscan.conectar();

    if(conectado){
        QMessageBox::information(this, "Dispositivo conectado", "El dispositivo ha sido conectado correctamente");
    }else{
        QMessageBox::critical(this, "Error al conectar", "El dispositivo no se pudo conectar");
    }

    revisionBtns();
}

void MainWindow::on_actionDesconectar_triggered()
{
    conectado = miniscan.desconectar();

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

void MainWindow::on_btnMedir_clicked()
{
    QList<QVariant> medicion;
    QVector<double> yRef(31), yAbs(31);

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

    int rango = 400;
    QModelIndex indice;
    for(int i = 0; i < 31; ++i){

        yRef[i] = medicion.at(i).toDouble();
        yAbs[i] = double(100) - medicion.at(i).toDouble();

        indice = modelo->index(0, i, QModelIndex());
        modelo->setData(indice, yRef[i]);

        indice = modelo->index(1, i, QModelIndex());
        modelo->setData(indice, rango);

        rango+=10;
    }

    if(reflectancia->numCurvas() > 0){

        reflectancia->quitarCurva();
    }
    reflectancia->agregarCurva(yRef);

    if(absorbancia->numCurvas() > 0){

        absorbancia->quitarCurva();
    }
    absorbancia->agregarCurva(yAbs);

    ui->lineaEritema->setText(QString().setNum(ops.eritema(yRef)));

    numCurvas += 1;

    revisionBtns();
}

void MainWindow::ajustarRefX(const QCPRange &newRange)
{
    reflectancia->ajustarGrafica("x", newRange, 400, 700);
}

void MainWindow::ajustarRefY(const QCPRange &newRange)
{
    reflectancia->ajustarGrafica("y", newRange, 0, yRef);
}

void MainWindow::ajustarAbsX(const QCPRange &newRange)
{
    absorbancia->ajustarGrafica("x", newRange, 400, 700);
}

void MainWindow::ajustarAbsY(const QCPRange &newRange)
{
    absorbancia->ajustarGrafica("y",  newRange, 0, yAbs);
}

void MainWindow::on_actionEstandarizar_Negro_triggered()
{
    bool estandarizado;
    QMessageBox::information(this, "Prepare la trampa de luz", "Asegurese de tener lista la trampa de luz");
    estandarizado = miniscan.estNegro();

    if(estandarizado){
        QMessageBox::information(this, "Color negro estandarizado", "El color negro ha sido estandarizado correctamente");
    }else{
        QMessageBox::critical(this, "Error al estandarizar", "No se pudo estandarizar el color negro");
    }

    revisionBtns();
}

void MainWindow::on_actionEstandarizar_Blanco_triggered()
{
    bool estandarizado;
    QMessageBox::information(this, "Prepare la cerámica blanca", "Asegurese de tener lista la cerámica blanca");
    estandarizado = miniscan.estBlanco();

    if(estandarizado){
        QMessageBox::information(this, "Color blanco estandarizado", "El color blanco ha sido estandarizado correctamente");
    }else{
        QMessageBox::critical(this, "Error al estandarizar", "No se pudo estandarizar el color blanco");
    }

    revisionBtns();
}

void MainWindow::on_refSpinY_valueChanged(double arg1)
{
    yRef = int(arg1 + 1);
    ui->graficaReflectancia->yAxis->setRange(0, double(arg1));
    ui->graficaReflectancia->replot();
}

void MainWindow::on_absSpinY_valueChanged(double arg1)
{
    yAbs = int(arg1 + 1);
    ui->graficaAbsorbancia->yAxis->setRange(0, double(arg1));
    ui->graficaAbsorbancia->replot();
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
