#ifndef DLGDATOSADICIONALES_H
#define DLGDATOSADICIONALES_H

#include <QDialog>
#include <QStandardItemModel>
#include <spectralops.h>

namespace Ui {
class dlgDatosAdicionales;
}

class dlgDatosAdicionales : public QDialog
{
    Q_OBJECT

public:
    explicit dlgDatosAdicionales(QVector<float> datosEspectrales, QWidget *parent = 0);
    ~dlgDatosAdicionales();

private slots:
    void on_btnListo_clicked();

private:
    Ui::dlgDatosAdicionales *ui;
    QStandardItemModel *modeloXYZ, *modeloLAB;
};

#endif // DLGDATOSADICIONALES_H
