#ifndef DLGREGLESION_H
#define DLGREGLESION_H

#include <QDialog>

namespace Ui {
class dlgRegLesion;
}

class dlgRegLesion : public QDialog
{
    Q_OBJECT

public:
    explicit dlgRegLesion(QWidget *parent = 0);
    ~dlgRegLesion();

private slots:
    void on_btnCancelar_clicked();

    void on_lineaNombre_textChanged(const QString &arg1);

    void on_lineaArea_textChanged(const QString &arg1);

private:
    Ui::dlgRegLesion *ui;
};

#endif // DLGREGLESION_H
