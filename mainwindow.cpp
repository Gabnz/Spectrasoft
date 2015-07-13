#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    yMax = 0;
    conectado = false;
    miniscan = new QAxObject;
    connect(ui->plotReflectancia->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(ajustarX(QCPRange)));
    connect(ui->plotReflectancia->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(ajustarY(QCPRange)));
    //si se puede usar el .dll sin registrar, pero hace falta determinar que estructura debe tener el .dll en vb.net para poderse usar de esa forma
    //miniscan->setControl(":/dll/MSXEBridge.dll");

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
    //ui->btnMedir->setEnabled(btnMedir);
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

    resultado = miniscan->dynamicCall("medirMuestra()");
    qDebug() << resultado << endl;

    medicion = resultado.toList();

    QList<QVariant>::const_iterator iter = qFind(medicion.begin(), medicion.end(), 0);

    if(iter == medicion.end()){
        //si no se consigue ningun cero exacto (0), es porque la lista fue llenada correctamente y por lo tanto la medicion ocurrio
    }else{
        medicion.clear();

        QMessageBox::critical(this, "Error al medir muestra", "La medicion no se pudo realizar");

        medicion.push_back(17.2101);
        medicion.push_back(15.2329);
        medicion.push_back(15.13);
        medicion.push_back(14.2457);
        medicion.push_back(16.0641);
        medicion.push_back(18.2752);
        medicion.push_back(19.687);
        medicion.push_back(21.0481);
        medicion.push_back(21.9136);
        medicion.push_back(23.1382);
        medicion.push_back(23.9694);
        medicion.push_back(25.4163);
        medicion.push_back(25.2229);
        medicion.push_back(24.8392);
        medicion.push_back(24.9241);
        medicion.push_back(25.2234);
        medicion.push_back(26.2638);
        medicion.push_back(26.5036);
        medicion.push_back(27.8098);
        medicion.push_back(31.5459);
        medicion.push_back(36.2515);
        medicion.push_back(39.0012);
        medicion.push_back(40.6161);
        medicion.push_back(42.1796);
        medicion.push_back(43.205);
        medicion.push_back(44.057);
        medicion.push_back(45.0165);
        medicion.push_back(45.779);
        medicion.push_back(46.4996);
        medicion.push_back(47.3194);
        medicion.push_back(47.8099);
    }

    float yMaxAux = std::numeric_limits<float>::min();
    float aux;
    int j = 400;

    for(int i = 0; i < 31; ++i){
        x[i] = j;
        y[i] = medicion.at(i).toDouble();

        aux = medicion.at(i).toFloat();

        if(aux > yMaxAux){
            yMaxAux = aux;
        }
        j+=10;
    }

    yMax = static_cast<int>(yMaxAux) + 1;

    ui->plotReflectancia->addGraph();
    ui->plotReflectancia->graph(0)->setData(x, y);
    ui->plotReflectancia->xAxis->setRange(400, 700);
    ui->plotReflectancia->yAxis->setRange(0, yMax);
    ui->plotReflectancia->xAxis->setLabel("Eje X");
    ui->plotReflectancia->yAxis->setLabel("Eje Y");
    ui->plotReflectancia->setInteraction(QCP::iRangeDrag, true);
    ui->plotReflectancia->setInteraction(QCP::iRangeZoom, true);
    ui->plotReflectancia->replot();

    revisionBtns();
}

void MainWindow::ajustarX(const QCPRange &newRange)
{
    QCPRange boundedRange = newRange;
    double lowerRangeBound = 400;
    double upperRangeBound = 700;
    if (boundedRange.size() > upperRangeBound-lowerRangeBound)
    {
      boundedRange = QCPRange(lowerRangeBound, upperRangeBound);
    } else
    {
      double oldSize = boundedRange.size();
      if (boundedRange.lower < lowerRangeBound)
      {
        boundedRange.lower = lowerRangeBound;
        boundedRange.upper = lowerRangeBound+oldSize;
      }
      if (boundedRange.upper > upperRangeBound)
      {
        boundedRange.lower = upperRangeBound-oldSize;
        boundedRange.upper = upperRangeBound;
      }
    }
    ui->plotReflectancia->xAxis->setRange(boundedRange);
}

void MainWindow::ajustarY(const QCPRange &newRange)
{
    QCPRange boundedRange = newRange;
    double lowerRangeBound = 0;
    double upperRangeBound = yMax;
    if (boundedRange.size() > upperRangeBound-lowerRangeBound)
    {
      boundedRange = QCPRange(lowerRangeBound, upperRangeBound);
    } else
    {
      double oldSize = boundedRange.size();
      if (boundedRange.lower < lowerRangeBound)
      {
        boundedRange.lower = lowerRangeBound;
        boundedRange.upper = lowerRangeBound+oldSize;
      }
      if (boundedRange.upper > upperRangeBound)
      {
        boundedRange.lower = upperRangeBound-oldSize;
        boundedRange.upper = upperRangeBound;
      }
    }
    ui->plotReflectancia->yAxis->setRange(boundedRange);
}
