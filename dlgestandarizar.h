#ifndef DLGESTANDARIZAR_H
#define DLGESTANDARIZAR_H

#include <QDialog>

namespace Ui {
class dlgEstandarizar;
}

class dlgEstandarizar : public QDialog
{
    Q_OBJECT

public:
    explicit dlgEstandarizar(QWidget *parent = 0);
    void estBlanco();
    ~dlgEstandarizar();

private slots:
    void on_btnListo_clicked();

private:
    Ui::dlgEstandarizar *ui;
};

#endif // DLGESTANDARIZAR_H
