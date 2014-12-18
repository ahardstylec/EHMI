#include "speedneedlenormal.h"
#include "global.h"
#include <QDebug>
#include <QMatrix>
#include <QMatrix4x4>
#include <QGraphicsRotation>

SpeedNeedleNormal::SpeedNeedleNormal() :
    SpeedNeedle(),
    QSvgViewItem("bilder/normal-speed_needle.svg", 610, 215)
{

}

SpeedNeedleNormal::~SpeedNeedleNormal()
{

}

void SpeedNeedleNormal::resize(qreal xpos, qreal ypos)
{
    setPos(xpos+xPosOffset, ypos+yPosOffset);
    setScale(SCALE_FACTOR);
    rotationPoint = QVector3D(boundingRect().width()*SCALE_FACTOR, 0 ,0);
}

void SpeedNeedleNormal::update(qreal value)
{
    QMatrix4x4 rotation4x4;
    QGraphicsRotation rotation;

    rotation.setOrigin(rotationPoint);
    rotation.setAngle(value*1.8);
    rotation.applyTo(&rotation4x4);
    QTransform transform= rotation4x4.toTransform();
    setTransform(transform);
}
