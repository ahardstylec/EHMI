#ifndef GASPEDAL_H
#define GASPEDAL_H

#include <QObject>
#include "qsvgviewitem.h"
#include <QVector3D>

class GasPedal : public QSvgViewItem
{
    Q_OBJECT
public:
    GasPedal(QString filename, qreal xPosOffset, qreal yPosOffset);
    ~GasPedal();

    virtual void resize(qreal xpos, qreal ypos)=0;
protected:
    QVector3D rotationPoint;
public slots:
    virtual void update(qreal value)=0;
};

#endif // GASPEDAL_H
