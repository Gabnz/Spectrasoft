#ifndef DLGREGHISTORIA_H
#define DLGREGHISTORIA_H

#include <QDialog>
#include <QRegularExpression>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <dlgconfirmarclave.h>

namespace Ui {
class dlgRegHistoria;
}

class dlgRegHistoria : public QDialog
{
    Q_OBJECT

public:
    explicit dlgRegHistoria(QString claveUsuario, QWidget *parent = 0);
    bool camposListos();
    ~dlgRegHistoria();

signals:
    void historia_registrada(QHash<QString, QString> info);

private slots:

    void on_btnCancelar_clicked();

    void on_lineaNombre_textChanged(const QString &arg1);

    void on_lineaApellido_textChanged(const QString &arg1);

    void on_cBoxSexo_currentIndexChanged(int index);

    void on_btnRegistrar_clicked();

    void on_claveIntroducida(bool correcta);

private:
    Ui::dlgRegHistoria *ui;
    bool nombreListo, apellidoListo, cedulaLista, fecha_nacLista, sexoListo;
    QHash<QString, QString> infoHistoria;
    QString clave;
};

#endif // DLGREGHISTORIA_H
