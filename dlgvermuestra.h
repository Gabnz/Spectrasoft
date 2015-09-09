#ifndef DLGVERMUESTRA_H
#define DLGVERMUESTRA_H

#include <QDialog>
#include <QDate>

namespace Ui {
class dlgVerMuestra;
}

class dlgVerMuestra : public QDialog
{
    Q_OBJECT

public:
    explicit dlgVerMuestra(QHash<QString, QString> infoMuestra, QWidget *parent = 0);
    ~dlgVerMuestra();

private slots:
    void on_btnListo_clicked();

private:
    Ui::dlgVerMuestra *ui;
};

#endif // DLGVERMUESTRA_H
