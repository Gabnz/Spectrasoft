#ifndef DLGGRAFICA_H
#define DLGGRAFICA_H

#include <QDialog>

namespace Ui {
class dlgGrafica;
}

class dlgGrafica : public QDialog
{
    Q_OBJECT

public:
    explicit dlgGrafica(QWidget *parent = 0);
    ~dlgGrafica();

private:
    Ui::dlgGrafica *ui;
};

#endif // DLGGRAFICA_H
