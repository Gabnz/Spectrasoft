#include "dlgfototipo.h"
#include "ui_dlgfototipo.h"

dlgFototipo::dlgFototipo(int fototipoRecomendadoExt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgFototipo)
{
    ui->setupUi(this);

    fototipoRecomendado = fototipoRecomendadoExt;
    ui->etqFototipoRecomendado->setPixmap(QPixmap(":/img/fototipo_" + QString().setNum(fototipoRecomendado) + ".png"));
    ui->etqNumeroRecomendado->setText(QString().setNum(fototipoRecomendado));

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
    this->close();
}

void dlgFototipo::on_btnListo_clicked()
{
    this->close();
}
