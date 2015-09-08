#ifndef DLGVERLESION_H
#define DLGVERLESION_H

#include <QDialog>
#include <QDate>

namespace Ui {
class dlgVerLesion;
}

class dlgVerLesion : public QDialog
{
    Q_OBJECT

public:
    explicit dlgVerLesion(QHash<QString, QString> infoLesion, QWidget *parent = 0);
    ~dlgVerLesion();

private slots:
    void on_btnListo_clicked();

private:
    Ui::dlgVerLesion *ui;
};

#endif // DLGVERLESION_H
