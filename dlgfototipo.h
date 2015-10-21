#ifndef DLGFOTOTIPO_H
#define DLGFOTOTIPO_H

#include <QDialog>
#include <QVector>
#include <QSignalMapper>
#include <QString>
#include <clasificador/objmsv.h>
#include <QtConcurrent/QtConcurrent>
#include <QDebug>

namespace Ui {
class dlgFototipo;
}

class dlgFototipo : public QDialog
{
    Q_OBJECT

public:
    explicit dlgFototipo(int fPredeterminado, QVector<float> LABext, QWidget *parent = 0);
    ~dlgFototipo();

signals:
    void fototipoSeleccionado(int numero);
    void resetearFototipo();

private slots:
    void seleccionFototipo(int fototipoSeleccionado);

    void on_btnCancelar_clicked();

    void on_btnListo_clicked();

public slots:
    void on_fototipoRecomendado(int resultado);

private:
    Ui::dlgFototipo *ui;
    QVector<float> LAB;
    QList<QPushButton*> btnsFototipos;
    QSignalMapper fototiposMapper;
    int fototipo, numFototipos, fototipoRecomendado;
    QSize tam, tamSeleccionado;
    objMsv clasificador;
};

#endif // DLGFOTOTIPO_H
