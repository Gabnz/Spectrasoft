#ifndef DLGADMINISTRARUSUARIOS_H
#define DLGADMINISTRARUSUARIOS_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringListModel>
#include <QDebug>
#include <dlgverusuario.h>
#include <dlgcambiarrol.h>
#include <dlgconfirmarclave.h>

namespace Ui {
class dlgAdministrarUsuarios;
}

class dlgAdministrarUsuarios : public QDialog
{
    Q_OBJECT

public:
    explicit dlgAdministrarUsuarios(QString cedulaUsuario, QString claveUsuario, QWidget *parent = 0);
    void revisionBtns();
    void buscar();
    bool existeCriterio();
    ~dlgAdministrarUsuarios();

private slots:
    void on_btnCancelar_clicked();

    void on_lineaNombre_textChanged(const QString &arg1);

    void on_lineaApellido_textChanged(const QString &arg1);

    void on_cBoxSexo_currentIndexChanged(int index);

    void on_cBoxRol_currentIndexChanged(int index);

    void on_checkBoxICI_toggled(bool checked);

    void on_checkBoxIFechaNac_toggled(bool checked);

    void on_cBoxCI_currentIndexChanged(int index);

    void on_lineaCI_textChanged(const QString &arg1);

    void on_editFechaNac_dateChanged(const QDate &date);

    void on_btnVer_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_btnRol_clicked();

    void on_rolCambiado(QString rol);

private:
    Ui::dlgAdministrarUsuarios *ui;
    QStringListModel *modelo;
    QHash<int, QString> ciUsuarios;
    QHash<QString, QString> infoUsuario;
    QString cedula, clave;
};

#endif // DLGADMINISTRARUSUARIOS_H
