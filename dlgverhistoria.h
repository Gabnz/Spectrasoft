#ifndef DLGVERHISTORIA_H
#define DLGVERHISTORIA_H

#include <QDialog>
#include <QDate>

namespace Ui {
class dlgVerHistoria;
}

class dlgVerHistoria : public QDialog
{
    Q_OBJECT

public:
    explicit dlgVerHistoria(QHash<QString, QString> infoHistoria, QWidget *parent = 0);
    ~dlgVerHistoria();

private slots:
    void on_btnListo_clicked();

private:
    Ui::dlgVerHistoria *ui;
};

#endif // DLGVERHISTORIA_H
