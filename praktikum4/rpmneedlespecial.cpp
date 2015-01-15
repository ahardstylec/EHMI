#include "rpmneedlespecial.h"

#include <QGraphicsTransform>
#include <QMatrix4x4>
RpmNeedleSpecial::RpmNeedleSpecial() :
RpmNeedle("data/bilder/special-rpm-1.svg", 557, 123)
{
    tempTwo = new QGraphicsSvgItem("data/bilder/special-rpm-2.svg");
    tempThree = new QGraphicsSvgItem("data/bilder/special-rpm-3.svg");
    tempFour = new QGraphicsSvgItem("data/bilder/special-rpm-4.svg");
}

RpmNeedleSpecial::~RpmNeedleSpecial()
{
    delete tempTwo;
    delete tempThree;
    delete tempFour;
}



void RpmNeedleSpecial::resize(qreal xpos, qreal ypos)
{
    rotationPoint = QVector3D(boundingRect().width()*2, boundingRect().height()/2 ,0);
    initResize(this, xpos, ypos);
    initResize(tempTwo, xpos, ypos);
    initResize(tempThree, xpos, ypos);
    initResize(tempFour, xpos, ypos);
}

QGraphicsSvgItem *RpmNeedleSpecial::getTempThreePtr()
{
    return tempThree;
}

QGraphicsSvgItem *RpmNeedleSpecial::getTempTwoPtr()
{
    return tempTwo;
}

QGraphicsSvgItem *RpmNeedleSpecial::getTempFourPtr()
{
    return tempFour;
}

void RpmNeedleSpecial::update(qreal value)
{
    tempFour->setOpacity((value-4000)/1000);
    tempThree->setOpacity((value-2500)/1500);
    tempTwo->setOpacity((value-1500)/1000);
    setOpacity(value/1500);
}

void RpmNeedleSpecial::initResize(QGraphicsSvgItem *item, qreal xpos, qreal ypos)
{
    item->setPos(xpos+xPosOffset, ypos+yPosOffset);
    item->setScale(0.34   );
    QMatrix4x4 rotation4x4;
    QGraphicsRotation rotation;
    rotation.setOrigin(rotationPoint);
    rotation.setAngle(4);
    rotation.applyTo(&rotation4x4);
    QTransform transform= rotation4x4.toTransform();
    item->setTransform(transform);
}

