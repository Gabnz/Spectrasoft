#ifndef DLGMODIFICARUSUARIO_H
#define DLGMODIFICARUSUARIO_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <dlgconfirmarclave.h>

namespace Ui {
class dlgModificarUsuario;
}

class dlgModificarUsuario : public QDialog
{
    Q_OBJECT

public:
    explicit dlgModificarUsuario(QHash<QString, QString> infoUsuario, QWidget *parent = 0);
    void revisionBtn();
    ~dlgModificarUsuario();

signals:
    void usuarioModificado(QHash<QString, QString> infoModificada);

private slots:
    void on_btnCancelar_clicked();

    void on_lineaNombre_textChanged(const QString &arg1);

    void on_lineaApellido_textChanged(const QString &arg1);

    void on_editFechaNac_dateChanged(const QDate &date);

    void on_cBoxSexo_currentTextChanged(const QString &arg1);

    void on_btnModificar_clicked();

    void on_claveIntroducida(bool correcta);

private:
    Ui::dlgModificarUsuario *ui;
    QHash<QString, QString> infoOriginal, infoNueva;
};

#endif // DLGMODIFICARUSUARIO_H
