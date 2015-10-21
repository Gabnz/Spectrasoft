#ifndef OBJMSV_H
#define OBJMSV_H

#include <QObject>
#include <QVector>
#include <clasificador/msv.h>
#include <QDebug>

class objMsv : public QObject
{
    Q_OBJECT
public:
    explicit objMsv(QObject *parent = 0);
    void start(QVector<float> LAB);
    ~objMsv();

signals:
    void fototipo_recomendado(int resultado);

public slots:
};

#endif // OBJMSV_H
