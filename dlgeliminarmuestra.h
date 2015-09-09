#ifndef DLGELIMINARMUESTRA_H
#define DLGELIMINARMUESTRA_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <dlgconfirmarclave.h>

namespace Ui {
class dlgEliminarMuestra;
}

class dlgEliminarMuestra : public QDialog
{
    Q_OBJECT

public:
    explicit dlgEliminarMuestra(QString idMuestra, QString claveUsuario, QWidget *parent = 0);
    ~dlgEliminarMuestra();

signals:
    void muestraEliminada();

private slots:
    void on_btnCancelar_clicked();

    void on_btnEliminar_clicked();

    void on_claveIntroducida(bool correcta);

private:
    Ui::dlgEliminarMuestra *ui;
    QString id, clave;
};

#endif // DLGELIMINARMUESTRA_H
