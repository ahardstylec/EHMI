#ifndef SPEEDNEEDLE_H
#define SPEEDNEEDLE_H

#include <QObject>
#include <QVector3D>
#include "qsvgviewitem.h"

class SpeedNeedle : public QSvgViewItem
{
    Q_OBJECT
public:
    SpeedNeedle();
    ~SpeedNeedle();
    QVector3D rotationPoint;

public slots:
    virtual void update(qreal value)= 0;

};

#endif // SPEEDNEEDLE_H
