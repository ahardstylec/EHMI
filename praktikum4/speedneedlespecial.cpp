#include "speedneedlespecial.h"

SpeedNeedleSpecial::SpeedNeedleSpecial(): SpeedNeedle("bilder/special-speed_needle.svg", 610, 215)
{

}

SpeedNeedleSpecial::~SpeedNeedleSpecial()
{

}

void SpeedNeedleSpecial::resize(qreal xpos, qreal ypos)
{
    setPos(xpos+xPosOffset, ypos+yPosOffset);
    setScale(SCALE_FACTOR);
    rotationPoint = QVector3D(boundingRect().width()*SCALE_FACTOR, 0 ,0);
}

void SpeedNeedleSpecial::update(qreal value)
{

}


