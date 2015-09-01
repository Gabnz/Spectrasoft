#ifndef DLGELIMINARUSUARIO_H
#define DLGELIMINARUSUARIO_H

#include <QDialog>

namespace Ui {
class dlgEliminarUsuario;
}

class dlgEliminarUsuario : public QDialog
{
    Q_OBJECT

public:
    explicit dlgEliminarUsuario(QWidget *parent = 0);
    ~dlgEliminarUsuario();

private slots:
    void on_btnCancelar_clicked();

private:
    Ui::dlgEliminarUsuario *ui;
};

#endif // DLGELIMINARUSUARIO_H
