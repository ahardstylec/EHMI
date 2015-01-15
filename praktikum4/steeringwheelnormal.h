#ifndef STEERINGWHEELNORMAL_H
#define STEERINGWHEELNORMAL_H

#include <QObject>
#include "steeringwheel.h"

class SteeringWheelNormal : public SteeringWheel
{
    Q_OBJECT
public:
    SteeringWheelNormal();
    ~SteeringWheelNormal();
    void resize(qreal xpos, qreal ypos);
    qreal xpos, ypos;

public slots:
    void update(int value);
};

#endif // STEERINGWHEELNORMAL_H
