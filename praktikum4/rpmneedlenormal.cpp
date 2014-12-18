#include "rpmneedlenormal.h"
#include <QGraphicsTransform>
#include <QMatrix4x4>

RpmNeedleNormal::RpmNeedleNormal():
    QSvgViewitem("data/bilder/normal-rpm_needle.svg", 217, 253),
    RpmNeedle()
{

}

RpmNeedleNormal::~RpmNeedleNormal()
{

}

void RpmNeedleNormal::resize(qreal xpos, qreal ypos)
{
    setPos(xpos+217, ypos+253);
    setScale(SCALE_FACTOR);
    rotationPoint = QVector3D(boundingRect().width()*SCALE_FACTOR, 0 ,0);
}

void RpmNeedleNormal::update(qreal value)
{
    QMatrix4x4 rotation4x4;
    QGraphicsRotation rotation;

    rotation.setOrigin(rotationPoint);
    rotation.setAngle(value*0.036);
    rotation.applyTo(&rotation4x4);
    QTransform transform= rotation4x4.toTransform();
    setTransform(transform);
}
