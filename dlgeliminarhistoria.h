#ifndef DLGELIMINARHISTORIA_H
#define DLGELIMINARHISTORIA_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <dlgconfirmarclave.h>

namespace Ui {
class dlgEliminarHistoria;
}

class dlgEliminarHistoria : public QDialog
{
    Q_OBJECT

public:
    explicit dlgEliminarHistoria(QString idHistoria, QString claveUsuario, QWidget *parent = 0);
    ~dlgEliminarHistoria();

signals:
    void historiaEliminada();

private slots:
    void on_btnCancelar_clicked();

    void on_btnEliminar_clicked();

    void on_claveIntroducida(bool correcta);

private:
    Ui::dlgEliminarHistoria *ui;
    QString id, clave;
};

#endif // DLGELIMINARHISTORIA_H
