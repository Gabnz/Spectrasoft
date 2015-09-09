#ifndef DLGMODIFICARLESION_H
#define DLGMODIFICARLESION_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <dlgconfirmarclave.h>

namespace Ui {
class dlgModificarLesion;
}

class dlgModificarLesion : public QDialog
{
    Q_OBJECT

public:
    explicit dlgModificarLesion(QString claveUsuario, QHash<QString, QString> infoLesion, QWidget *parent = 0);
    ~dlgModificarLesion();

signals:
    void lesionModificada(QHash<QString, QString> infoModificada);

private slots:
    void on_btnCancelar_clicked();

    void on_lineaNombre_textChanged(const QString &arg1);

    void on_lineaArea_textChanged(const QString &arg1);

    void on_textEditObservaciones_textChanged();

    void on_btnModificar_clicked();

    void on_claveIntroducida(bool correcta);

private:
    Ui::dlgModificarLesion *ui;
    QHash<QString, QString> infoOriginal, infoNueva;
    QString clave;
};

#endif // DLGMODIFICARLESION_H
