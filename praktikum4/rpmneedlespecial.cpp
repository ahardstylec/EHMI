#include "rpmneedlespecial.h"

#include <QGraphicsTransform>
#include <QMatrix4x4>
RpmNeedleSpecial::RpmNeedleSpecial() :
RpmNeedle("data/bilder/special-rpm.svg", 557, 123)
{

}

RpmNeedleSpecial::~RpmNeedleSpecial()
{

}
void RpmNeedleSpecial::resize(qreal xpos, qreal ypos)
{
    setPos(xpos+xPosOffset, ypos+yPosOffset);
    setScale(0.34   );
    rotationPoint = QVector3D(boundingRect().width()*2, boundingRect().height()/2 ,0);
    QMatrix4x4 rotation4x4;
    QGraphicsRotation rotation;
    rotation.setOrigin(rotationPoint);
    rotation.setAngle(4);
    rotation.applyTo(&rotation4x4);
    QTransform transform= rotation4x4.toTransform();
    setTransform(transform);
}

void RpmNeedleSpecial::update(qreal value)
{

}

