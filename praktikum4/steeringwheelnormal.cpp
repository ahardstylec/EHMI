#include "steeringwheelnormal.h"
#include "global.h"
#include <QDebug>

SteeringWheelNormal::SteeringWheelNormal() :
    SteeringWheel(),
    QSvgViewItem("data/bilder/normal-steering_wheel.svg",402, 96)
{

}

SteeringWheelNormal::~SteeringWheelNormal()
{

}


void SteeringWheelNormal::resize(qreal xpos, qreal ypos)
{
    this->xpos = xpos;
    this->ypos = ypos;
    setPos(xpos + xPosOffset, ypos+ yPosOffset);
    setScale(SCALE_FACTOR);
}

void SteeringWheelNormal::update(int value)
{
    QTransform transform;
    setPos(xpos+402, ypos+ 100);
    transform.translate(value/4+5, 0);
    setTransform(transform);
}
