#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAxObject>
#include <QAxBase>
#include <QAxWidget>
#include <QtSerialPort>
#include <QDebug>
///
#include <qcustomplot.h>
#include <limits>
///
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void revisionBtns();
    ~MainWindow();

private slots:
    void on_actionConectar_triggered();

    void on_actionDesconectar_triggered();

    void on_actionSalir_triggered();

    void on_btnMedir_clicked();

    void ajustarX(const QCPRange &newRange);
    void ajustarY(const QCPRange &newRange);

    void on_actionEstandarizar_Negro_triggered();

    void on_actionEstandarizar_Blanco_triggered();

    void on_spinY_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    QAxObject *miniscan;
    int puertoCOM, yMax, numCurvas;
    QVector<double> x;
    bool conectado;
};

#endif // MAINWINDOW_H
