#ifndef DLGMODIFICARHISTORIA_H
#define DLGMODIFICARHISTORIA_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <dlgconfirmarclave.h>

namespace Ui {
class dlgModificarHistoria;
}

class dlgModificarHistoria : public QDialog
{
    Q_OBJECT

public:
    explicit dlgModificarHistoria(QString claveUsuario, QHash<QString, QString> infoHistoria, QWidget *parent = 0);
    bool historiaModificada();
    QHash<QString, QString> getInfoHistoria();
    ~dlgModificarHistoria();

private slots:
    void on_btnCancelar_clicked();

    void on_lineaNombre_textChanged(const QString &arg1);

    void on_lineaApellido_textChanged(const QString &arg1);

    void on_btnModificar_clicked();

    void on_cBoxCI_currentTextChanged(const QString &arg1);

    void on_lineaCI_textChanged(const QString &arg1);

    void on_editFechaNac_dateChanged(const QDate &date);

    void on_cBoxSexo_currentTextChanged(const QString &arg1);

private:
    Ui::dlgModificarHistoria *ui;
    QHash<QString, QString> infoOriginal, infoNueva;
    bool modificada;
    QString clave;
};

#endif // DLGMODIFICARHISTORIA_H
