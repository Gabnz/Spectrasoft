#ifndef DLGBUSCARMUESTRA_H
#define DLGBUSCARMUESTRA_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringListModel>
#include <QDebug>
#include <dlgvermuestra.h>

namespace Ui {
class dlgBuscarMuestra;
}

class dlgBuscarMuestra : public QDialog
{
    Q_OBJECT

public:
    explicit dlgBuscarMuestra(QString idHistoria, QWidget *parent = 0);
    void buscar();
    bool existeCriterio();
    ~dlgBuscarMuestra();

signals:
    void muestraAbierta(QHash<QString, QString> infoM, float infoDatos[2][31], float infoCoordenadas[2][3], float infoEritema);

private slots:
    void on_cBoxTipo_currentIndexChanged(int index);

    void on_lineaNombre_textChanged(const QString &arg1);

    void on_lineaArea_textChanged(const QString &arg1);

    void on_checkBoxIFechaM_toggled(bool checked);

    void on_listView_clicked(const QModelIndex &index);

    void on_btnVer_clicked();

    void on_btnAbrir_clicked();

    void on_btnCancelar_clicked();

    void on_editFechaM_dateChanged(const QDate &date);

private:
    Ui::dlgBuscarMuestra *ui;
    QStringListModel *modelo;
    QString historia;
    QHash<int, QString> idMuestras;
    QHash<QString, QString> infoMuestra;
};

#endif // DLGBUSCARMUESTRA_H
