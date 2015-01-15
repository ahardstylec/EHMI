#include "speedneedlespecial.h"
#include <QMatrix>
#include <QMatrix4x4>
#include <QGraphicsRotation>

SpeedNeedleSpecial::SpeedNeedleSpecial() :
    SpeedNeedle("data/bilder/special-speed.svg", 420, 205)
{

}

SpeedNeedleSpecial::~SpeedNeedleSpecial()
{

}

void SpeedNeedleSpecial::resize(qreal xpos, qreal ypos)
{
    setPos(xpos+xPosOffset, ypos+yPosOffset);
    rotationPoint = QVector3D(boundingRect().width()*SCALE_FACTOR, 0 ,0);
    setScale(SCALE_FACTOR);
}

void SpeedNeedleSpecial::update(qreal value)
{
    QMatrix4x4 rotation4x4;
    QGraphicsRotation rotation;

    rotation.setOrigin(rotationPoint);
    rotation.setAngle(value*1.8);
    rotation.applyTo(&rotation4x4);
    QTransform transform= rotation4x4.toTransform();
    setTransform(transform);
}


