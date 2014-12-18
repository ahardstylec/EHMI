#ifndef STEERINGWHEELSPECIAL_H
#define STEERINGWHEELSPECIAL_H

#include <QObject>
#include "steeringwheel.h"

class SteeringWheelSpecial : public SteeringWheel
{
    Q_OBJECT
public:
    SteeringWheelSpecial();
    ~SteeringWheelSpecial();
    void resize(qreal xpos, qreal ypos);
    qreal xPosOffset;
    qreal yPosOffset;

public slots:
    void update(int value);
};

#endif // STEERINGWHEELSPECIAL_H
