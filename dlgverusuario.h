#ifndef DLGVERUSUARIO_H
#define DLGVERUSUARIO_H

#include <QDialog>
#include <QHash>

namespace Ui {
class dlgVerUsuario;
}

class dlgVerUsuario : public QDialog
{
    Q_OBJECT

public:
    explicit dlgVerUsuario(QHash<QString, QString> infoUsuario, QWidget *parent = 0);
    ~dlgVerUsuario();

private slots:
    void on_btnListo_clicked();

private:
    Ui::dlgVerUsuario *ui;
};

#endif // DLGVERUSUARIO_H
