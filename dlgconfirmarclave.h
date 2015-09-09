#ifndef DLGCONFIRMARCLAVE_H
#define DLGCONFIRMARCLAVE_H

#include <QDialog>

namespace Ui {
class dlgConfirmarClave;
}

class dlgConfirmarClave : public QDialog
{
    Q_OBJECT

public:
    explicit dlgConfirmarClave(QString claveUsuario, QWidget *parent = 0);
    ~dlgConfirmarClave();

signals:
    void claveIntroducida(bool correcta);

private slots:
    void on_lineaClave_textChanged(const QString &arg1);

    void on_btnContinuar_clicked();

private:
    Ui::dlgConfirmarClave *ui;
    QString clave;
};

#endif // DLGCONFIRMARCLAVE_H
