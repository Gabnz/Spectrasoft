#ifndef DLGREGHISTORIA_H
#define DLGREGHISTORIA_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class dlgRegHistoria;
}

class dlgRegHistoria : public QDialog
{
    Q_OBJECT

public:
    explicit dlgRegHistoria(QWidget *parent = 0);
    ~dlgRegHistoria();

private slots:

    void on_btnCancelar_clicked();

    void on_lineaNombre_textChanged(const QString &arg1);

    void on_lineaApellido_textChanged(const QString &arg1);

private:
    Ui::dlgRegHistoria *ui;
};

#endif // DLGREGHISTORIA_H
