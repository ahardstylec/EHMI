#include "temperaturebarspecial.h"
#include <QGraphicsTransform>
#include <QMatrix4x4>

TemperatureBarSpecial::TemperatureBarSpecial() :
    TemperatureBar("data/bilder/special-temperature.svg", 373,102)
{
}

TemperatureBarSpecial::~TemperatureBarSpecial()
{
}

void TemperatureBarSpecial::resize(qreal xpos, qreal ypos)
{
    setPos(xpos + this->xPosOffset , ypos + this->yPosOffset );
    setScale(0.31);
    rotationPoint = QVector3D(boundingRect().width(), boundingRect().height() ,0);
    QMatrix4x4 rotation4x4;
    QGraphicsRotation rotation;
    rotation.setOrigin(rotationPoint);
    rotation.setAngle(-5);
    rotation.applyTo(&rotation4x4);
    QTransform transform= rotation4x4.toTransform();
    setTransform(transform);
}

void TemperatureBarSpecial::update(qreal value)
{

}
