#include "temperaturebarspecial.h"
#include <QGraphicsTransform>
#include <QMatrix4x4>

TemperatureBarSpecial::TemperatureBarSpecial() :
    TemperatureBar("data/bilder/special-temperature-3.svg", 217, -282)
{
    this->originalHeight= boundingRect().height();
    this->originalWidth= boundingRect().width();
    setTransformOriginPoint ( originalWidth, originalHeight );
    tempTwo = new QGraphicsSvgItem("data/bilder/special-temperature-2.svg");
    tempThree = new QGraphicsSvgItem("data/bilder/special-temperature-1.svg");
    tempTwo->setTransformOriginPoint(originalWidth, originalHeight );
    tempThree->setTransformOriginPoint(originalWidth, originalHeight );
}

TemperatureBarSpecial::~TemperatureBarSpecial()
{
    delete tempTwo;
    delete tempThree;
}

void TemperatureBarSpecial::initResize(QGraphicsSvgItem * item, qreal xpos, qreal ypos){
    item->setPos(xpos + this->xPosOffset , ypos + this->yPosOffset );
    item->setScale(0.35);

    QMatrix4x4 rotation4x4;
    QGraphicsRotation rotation;
    rotation.setOrigin(rotationPoint);
    rotation.setAngle(-7);
    rotation.applyTo(&rotation4x4);
    QTransform transform= rotation4x4.toTransform();
    transform.scale(1.05, 1);
    item->setTransform(transform);
}

void TemperatureBarSpecial::resize(qreal xpos, qreal ypos)
{
    rotationPoint = QVector3D(boundingRect().width(), boundingRect().height() ,0);
    initResize(this, xpos,ypos);
    initResize(tempTwo, xpos,ypos);
    initResize(tempThree,xpos,ypos);
    tempTwo->setVisible(true);
    tempThree->setVisible(true);
    setVisible(true);
}

QGraphicsSvgItem *TemperatureBarSpecial::getTempThreePtr()
{
    return tempThree;
}

QGraphicsSvgItem *TemperatureBarSpecial::getTempTwoPtr()
{
    return tempTwo;
}

void TemperatureBarSpecial::update(qreal value)
{
    tempThree->setOpacity((value-90)/30);
    tempTwo->setOpacity((value-70)/20);
    setOpacity((value-50)/20);
}
