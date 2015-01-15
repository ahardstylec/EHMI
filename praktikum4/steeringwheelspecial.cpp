#include "steeringwheelspecial.h"
#include <QGraphicsTransform>
#include <QMatrix4x4>

SteeringWheelSpecial::SteeringWheelSpecial():
    SteeringWheel("data/bilder/special-steering_wheel.svg", 475, 70)
{

}

SteeringWheelSpecial::~SteeringWheelSpecial()
{

}


void SteeringWheelSpecial::resize(qreal xpos, qreal ypos)
{
    setPos(xpos + this->xPosOffset, ypos+ this->yPosOffset);
    setScale(SCALE_FACTOR);
    rotationPoint = QVector3D((boundingRect().width()*SCALE_FACTOR)/2, (boundingRect().height()*2)+80 ,0);
}

void SteeringWheelSpecial::update(int value)
{
    QMatrix4x4 rotation4x4;
    QGraphicsRotation rotation;

    rotation.setOrigin(rotationPoint);
    rotation.setAngle(value*0.043);
    rotation.applyTo(&rotation4x4);
    QTransform transform= rotation4x4.toTransform();
    setTransform(transform);
}
