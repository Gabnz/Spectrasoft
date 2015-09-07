#ifndef DLGREGFOTOTIPO_H
#define DLGREGFOTOTIPO_H

#include <QDialog>
#include <dlgfototipo.h>
#include <spectralops.h>

namespace Ui {
class dlgRegFototipo;
}

class dlgRegFototipo : public QDialog
{
    Q_OBJECT

public:
    explicit dlgRegFototipo(QWidget *parent = 0);
    ~dlgRegFototipo();

private slots:
    void on_btnCancelar_clicked();

    void on_lineaNombre_textChanged(const QString &arg1);

    void on_lineaArea_textChanged(const QString &arg1);

    void on_btnFototipo_clicked();

    void on_resetearFototipo();

    void on_fototipo(int numero);

private:
    Ui::dlgRegFototipo *ui;
    int fototipo;
};

#endif // DLGREGFOTOTIPO_H
