#ifndef GASPEDAL_H
#define GASPEDAL_H

#include <QObject>
#include "qsvgviewitem.h"
#include <QVector3D>

class GasPedal : public QGraphicsSvgItem
{
    Q_OBJECT
public:
    GasPedal(QString filename);
    ~GasPedal();

private:
    QVector3D rotationPoint;
public slots:
    virtual void update(qreal value)=0;
};

#endif // GASPEDAL_H
