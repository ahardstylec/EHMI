#include "gaspedalnormal.h"
#include <QGraphicsTransform>
#include <QMatrix4x4>

GasPedalNormal::GasPedalNormal() :
    GasPedal("data/bilder/normal-gas_pedal.svg", 438, 215)
{

}

GasPedalNormal::~GasPedalNormal()
{

}

void GasPedalNormal::resize(qreal xpos, qreal ypos)
{
    setPos(xpos +this->xPosOffset, ypos+ this->yPosOffset);
    setScale(SCALE_FACTOR);
    rotationPoint = QVector3D(0, boundingRect().height()*SCALE_FACTOR ,0);
}

void GasPedalNormal::update(qreal value)
{
    QMatrix4x4 rotation4x4;
    QGraphicsRotation rotation;

    rotation.setOrigin(rotationPoint);
    rotation.setAngle(value*0.4);
    rotation.applyTo(&rotation4x4);
    QTransform transform= rotation4x4.toTransform();
    setTransform(transform);
}
