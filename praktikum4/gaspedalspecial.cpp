#include "gaspedalspecial.h"

GasPedalSpecial::GasPedalSpecial() :
    GasPedal("data/bilder/special-gas_pedal.svg", 733, -161)
{
    this->originalHeight= boundingRect().height();
    setTransformOriginPoint ( 0, originalHeight );
}

GasPedalSpecial::~GasPedalSpecial(      )
{

}

void GasPedalSpecial::resize(qreal xpos, qreal ypos)
{
    setPos(xpos +this->xPosOffset, ypos+ this->yPosOffset);
    setScale(0.31);
}

void GasPedalSpecial::update(qreal value)
{
    qreal newscale = value/100;
    QTransform transform;
    transform.translate(0, originalHeight - (originalHeight *newscale));
    transform = transform.scale(1, newscale);
    setTransform(transform);
}
