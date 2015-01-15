#ifndef STEERINGWHEELSPECIAL_H
#define STEERINGWHEELSPECIAL_H

#include <QObject>
#include <QVector3D>
#include "steeringwheel.h"

class SteeringWheelSpecial : public SteeringWheel
{
    Q_OBJECT
public:
    SteeringWheelSpecial();
    ~SteeringWheelSpecial();
    void resize(qreal xpos, qreal ypos);
    QVector3D rotationPoint;

public slots:
    void update(int value);
};

#endif // STEERINGWHEELSPECIAL_H
