#include "steeringwheelspecial.h"

SteeringWheelSpecial::SteeringWheelSpecial():
    SteeringWheel(),
    QSvgViewItem("data/bilder/special-steering_wheel.svg",402, 96)
{

}

SteeringWheelSpecial::~SteeringWheelSpecial()
{

}


void SteeringWheelSpecial::resize(qreal xpos, qreal ypos)
{
    this->xpos = xpos;
    this->ypos = ypos;
    setPos(xpos + xPosOffset, ypos+ yPosOffset);
    setScale(SCALE_FACTOR);
}

void SteeringWheelSpecial::update(int value)
{

}
