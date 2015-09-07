#ifndef DLGFOTOTIPO_H
#define DLGFOTOTIPO_H

#include <QDialog>
#include <QSignalMapper>
#include <QString>
#include <QDebug>

namespace Ui {
class dlgFototipo;
}

class dlgFototipo : public QDialog
{
    Q_OBJECT

public:
    explicit dlgFototipo(int fPredeterminado, int fototipoRecomendadoExt, QWidget *parent = 0);
    ~dlgFototipo();

signals:
    void fototipoSeleccionado(int numero);
    void resetearFototipo();

private slots:
    void seleccionFototipo(int fototipoSeleccionado);

    void on_btnCancelar_clicked();

    void on_btnListo_clicked();

private:
    Ui::dlgFototipo *ui;
    QList<QPushButton*> btnsFototipos;
    QSignalMapper fototiposMapper;
    int fototipo, numFototipos, fototipoRecomendado;
    QSize tam, tamSeleccionado;
};

#endif // DLGFOTOTIPO_H
