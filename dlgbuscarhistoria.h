#ifndef DLGBUSCARHISTORIA_H
#define DLGBUSCARHISTORIA_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringListModel>
#include <QDebug>
#include <dlgverhistoria.h>

namespace Ui {
class dlgBuscarHistoria;
}

class dlgBuscarHistoria : public QDialog
{
    Q_OBJECT

public:
    explicit dlgBuscarHistoria(QWidget *parent = 0);
    void buscar();
    bool existeCriterio();
    ~dlgBuscarHistoria();

signals:
    void historiaAbierta(QHash<QString, QString> info);

private slots:
    void on_btnCancelar_clicked();

    void on_checkBoxICI_toggled(bool checked);

    void on_checkBoxIFototipo_toggled(bool checked);

    void on_checkBoxIFechaNac_toggled(bool checked);

    void on_lineaNombre_textChanged(const QString &arg1);

    void on_lineaApellido_textChanged(const QString &arg1);

    void on_listView_clicked(const QModelIndex &index);

    void on_btnVer_clicked();

    void on_cBoxSexo_currentIndexChanged(int index);

    void on_lineaCI_textChanged(const QString &arg1);

    void on_cBoxCI_currentIndexChanged(int index);

    void on_btnAbrir_clicked();

    void on_editFechaNac_dateChanged(const QDate &date);

    void on_cBoxFototipo_currentIndexChanged(int index);

private:
    Ui::dlgBuscarHistoria *ui;
    QStringListModel *modelo;
    QHash<int, QString> idHistorias;
    QHash<QString, QString> infoHistoria;
};

#endif // DLGBUSCARHISTORIA_H
