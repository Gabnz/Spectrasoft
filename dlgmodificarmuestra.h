#ifndef DLGMODIFICARMUESTRA_H
#define DLGMODIFICARMUESTRA_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <dlgconfirmarclave.h>

namespace Ui {
class dlgModificarMuestra;
}

class dlgModificarMuestra : public QDialog
{
    Q_OBJECT

public:
    explicit dlgModificarMuestra(QString claveUsuario, QHash<QString, QString> infoMuestra, QWidget *parent = 0);
    ~dlgModificarMuestra();

signals:
    void muestraModificada(QHash<QString, QString> infoModificada);

private slots:
    void on_btnCancelar_clicked();

    void on_lineaNombre_textChanged(const QString &arg1);

    void on_lineaArea_textChanged(const QString &arg1);

    void on_textEditObservaciones_textChanged();

    void on_btnModificar_clicked();

    void on_claveIntroducida(bool correcta);

private:
    Ui::dlgModificarMuestra *ui;
    QHash<QString, QString> infoOriginal, infoNueva;
    QString clave;
};

#endif // DLGMODIFICARMUESTRA_H
