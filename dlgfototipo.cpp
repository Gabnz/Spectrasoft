#include "dlgfototipo.h"
#include "ui_dlgfototipo.h"

dlgFototipo::dlgFototipo(int fPredeterminado, QVector<float> LABext, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgFototipo)
{
    ui->setupUi(this);

    LAB = LABext;
    //conectando y creando un hilo de ejecucion para correr el algoritomo de clasificacion del fototipo
    connect(&clasificador, &objMsv::fototipo_recomendado, this, &dlgFototipo::on_fototipoRecomendado);
    QFuture<void> hiloClasificacion = QtConcurrent::run(&this->clasificador, &objMsv::start, LAB);

    btnsFototipos.push_back(ui->btnFototipo1);
    btnsFototipos.push_back(ui->btnFototipo2);
    btnsFototipos.push_back(ui->btnFototipo3);
    btnsFototipos.push_back(ui->btnFototipo4);
    btnsFototipos.push_back(ui->btnFototipo5);
    btnsFototipos.push_back(ui->btnFototipo6);

    numFototipos = 6;

    for(int i = 0; i < numFototipos; ++i){
        connect(btnsFototipos.at(i), SIGNAL(clicked()), &fototiposMapper, SLOT(map()));
        fototiposMapper.setMapping(btnsFototipos.at(i), i + 1);
    }

    connect(&fototiposMapper, SIGNAL(mapped(int)), this, SLOT(seleccionFototipo(int)));

    fototipo = 0;
    tam.setWidth(125);
    tam.setHeight(125);
    tamSeleccionado.setWidth(145);
    tamSeleccionado.setHeight(145);
    ui->btnListo->setEnabled(false);

    if(fPredeterminado != 0){
        seleccionFototipo(fPredeterminado);
    }

    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
}

dlgFototipo::~dlgFototipo()
{
    delete ui;
}

void dlgFototipo::seleccionFototipo(int fototipoSeleccionado)
{
    bool btnListo;

    if(fototipo != 0 && fototipo != fototipoSeleccionado){
        btnsFototipos.at(fototipo - 1)->setIcon(QIcon(":/img/fototipo_" + QString().setNum(fototipo) + ".png"));
        btnsFototipos.at(fototipo - 1)->setIconSize(tam);
    }

    if(fototipo != fototipoSeleccionado){
        btnsFototipos.at(fototipoSeleccionado - 1)->setIcon(QIcon(":/img/fototipo_" + QString().setNum(fototipoSeleccionado) + "_seleccionado.png"));
        btnsFototipos.at(fototipoSeleccionado - 1)->setIconSize(tamSeleccionado);

        fototipo = fototipoSeleccionado;
        btnListo = true;
    }else{
        btnsFototipos.at(fototipoSeleccionado - 1)->setIcon(QIcon(":/img/fototipo_" + QString().setNum(fototipoSeleccionado) + ".png"));
        btnsFototipos.at(fototipoSeleccionado - 1)->setIconSize(tam);

        fototipo = 0;
        btnListo = false;
    }

    ui->btnListo->setEnabled(btnListo);
}

void dlgFototipo::on_btnCancelar_clicked()
{
    if(fototipo == 0)
        emit resetearFototipo();

    this->close();
}

void dlgFototipo::on_btnListo_clicked()
{
    emit fototipoSeleccionado(fototipo);
    this->close();
}

void dlgFototipo::on_fototipoRecomendado(int resultado)
{
    fototipoRecomendado = resultado;
    ui->etqFototipoRecomendado->setPixmap(QPixmap(":/img/fototipo_" + QString().setNum(fototipoRecomendado) + ".png"));

    QString aux;

    switch (fototipoRecomendado) {
    case 1:
        aux = "I";
        break;
    case 2:
        aux = "II";
        break;
    case 3:
        aux = "III";
        break;
    case 4:
        aux = "IV";
        break;
    case 5:
        aux = "V";
        break;
    case 6:
        aux = "VI";
        break;
    }

    ui->etqTituloRecomendado->setText("Fototipo recomendado:");
    ui->etqNumeroRecomendado->setText(aux);
}
