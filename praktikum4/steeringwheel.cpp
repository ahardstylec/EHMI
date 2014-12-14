#include "steeringwheel.h"
#include "global.h"

SteeringWheel::SteeringWheel() : QGraphicsSvgItem("data/bilder/normal-steering_wheel.svg")
{

}

SteeringWheel::~SteeringWheel()
{

}

void SteeringWheel::resize(qreal xpos, qreal ypos)
{
    setPos(xpos +402, ypos+ 100);
    setScale(SCALE_FACTOR);
}

void SteeringWheel::update(qreal value)
{

}

