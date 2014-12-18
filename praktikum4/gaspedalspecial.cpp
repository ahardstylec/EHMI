#include "gaspedalspecial.h"

GasPedalSpecial::GasPedalSpecial() :
    GasPedal(),
    QSvgViewItem("data/bilder/special-gas_pedal.svg")
{

}

GasPedalSpecial::~GasPedalSpecial()
{

}

void GasPedalSpecial::resize(qreal xpos, qreal ypos)
{
    setPos(xpos +this->xPosOffset, ypos+ this->yPosOffset);
    setScale(SCALE_FACTOR);
}

void GasPedalSpecial::update(qreal value)
{
}
