#ifndef DLGACERCADE_H
#define DLGACERCADE_H

#include <QDialog>

namespace Ui {
class dlgAcercaDe;
}

class dlgAcercaDe : public QDialog
{
    Q_OBJECT

public:
    explicit dlgAcercaDe(QWidget *parent = 0);
    ~dlgAcercaDe();

private slots:
    void on_btnCerrar_clicked();

private:
    Ui::dlgAcercaDe *ui;
};

#endif // DLGACERCADE_H
