#ifndef DLGTIPOMUESTRA_H
#define DLGTIPOMUESTRA_H

#include <QDialog>

namespace Ui {
class dlgTipoMuestra;
}

class dlgTipoMuestra : public QDialog
{
    Q_OBJECT

public:
    explicit dlgTipoMuestra(QWidget *parent = 0);
    ~dlgTipoMuestra();

signals:
    void tipo_muestra(QString tipo);

private slots:
    void on_btnCancelar_clicked();

    void on_btnFototipo_clicked();

    void on_btnLesion_clicked();

private:
    Ui::dlgTipoMuestra *ui;
};

#endif // DLGTIPOMUESTRA_H
