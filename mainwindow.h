#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAxObject>
#include <QAxBase>
#include <QAxWidget>
#include <QDebug>

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

private:
    Ui::MainWindow *ui;
    QAxObject *miniscan;
    bool conectado;
};

#endif // MAINWINDOW_H
