#include "dlggrafica.h"
#include "ui_dlggrafica.h"

dlgGrafica::dlgGrafica(QString tituloExt, QString etqX, QString etqY, int yMaxExt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgGrafica)
{
    ui->setupUi(this);

    n = 0;
    yMax = yMaxExt;

    QCPPlotTitle *titulo = new QCPPlotTitle(ui->grafica);

    titulo->setText(tituloExt);
    titulo->setFont(QFont("sans", 12, QFont::Bold));

    QVector<double> ticks;
    int j = 400;

    for(int i = 0; i < 31; ++i){
        ticks.push_back(double(j));
        x.push_back(j);
        j+=10;
    }

    ui->grafica->plotLayout()->insertRow(0);
    ui->grafica->plotLayout()->addElement(0, 0, titulo);
    ui->grafica->xAxis->setRange(400, 700);
    ui->grafica->xAxis->setLabel(etqX);
    ui->grafica->yAxis->setLabel(etqY);
    ui->grafica->xAxis->setAutoTicks(false);
    ui->grafica->xAxis->setTickVector(ticks);
    ui->grafica->xAxis->setTickLabelPadding(5);
    ui->grafica->xAxis->setTickLabelRotation(-45);
    ui->grafica->xAxis->setAutoTickStep(true);
    ui->grafica->setInteraction(QCP::iRangeDrag, true);
    ui->grafica->setInteraction(QCP::iRangeZoom, true);
    ui->grafica->setInteraction(QCP::iSelectItems, true);

    connect(ui->grafica->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(ajustarX(QCPRange)));
    connect(ui->grafica->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(ajustarY(QCPRange)));

    ui->spinY->setValue(yMax);
    ui->grafica->rescaleAxes();
    ui->grafica->yAxis->setTickStep(1);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
}

void dlgGrafica::agregarCurva(QVector<double> y)
{
    QCPScatterStyle myScatter;
    QPen pen;

    pen.setColor(Qt::black);
    pen.setWidth(1);
    myScatter.setShape(QCPScatterStyle::ssDisc);
    myScatter.setPen(pen);
    myScatter.setSize(5);
    ui->grafica->addGraph();
    ui->grafica->graph(n)->setData(x, y);
    ui->grafica->graph(n)->setScatterStyle(myScatter);
    ui->grafica->graph(n)->setPen(QPen(Qt::black));
    ui->grafica->yAxis->setRange(0, yMax);
    ui->grafica->replot();

    ++n;
}

void dlgGrafica::ajustarGrafica(QString axis, const QCPRange &newRange, double lower, double upper)
{
    QCPRange boundedRange = newRange;

    double lowerRangeBound = lower;
    double upperRangeBound = upper;

    if(boundedRange.size() > upperRangeBound - lowerRangeBound){
        boundedRange = QCPRange(lowerRangeBound, upperRangeBound);
    }else{
        double oldSize = boundedRange.size();

        if(boundedRange.lower < lowerRangeBound){
            boundedRange.lower = lowerRangeBound;
            boundedRange.upper = lowerRangeBound + oldSize;
        }

        if(boundedRange.upper > upperRangeBound){
            boundedRange.lower = upperRangeBound - oldSize;
            boundedRange.upper = upperRangeBound;
        }
    }

    if(axis == "x"){
        ui->grafica->xAxis->setRange(boundedRange);
    }else{
        ui->grafica->yAxis->setRange(boundedRange);
    }
}

dlgGrafica::~dlgGrafica()
{
    delete ui;
}

void dlgGrafica::ajustarX(const QCPRange &newRange)
{
    ajustarGrafica("x", newRange, 400, 700);
}

void dlgGrafica::ajustarY(const QCPRange &newRange)
{
    ajustarGrafica("y", newRange, 0, yMax);
}

void dlgGrafica::on_spinY_valueChanged(double arg1)
{
    yMax = int(arg1 + 1);
    ui->grafica->yAxis->setRange(0, double(arg1));
    ui->grafica->replot();
}
