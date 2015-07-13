#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAxObject>
#include <QAxBase>
#include <QAxWidget>
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

    void on_actionCalibrar_Blanco_triggered();

    void on_actionCalibrar_Negro_triggered();

    void on_btnMedir_clicked();

    void ajustarX(const QCPRange &newRange);
    void ajustarY(const QCPRange &newRange);

private:
    Ui::MainWindow *ui;
    QAxObject *miniscan;
    int yMax;
    bool conectado;
};

#endif // MAINWINDOW_H
