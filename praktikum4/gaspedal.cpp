#include "gaspedal.h"
#include "global.h"

GasPedal::GasPedal() : QGraphicsSvgItem("data/bilder/normal-gas_pedal.svg")
{

}

GasPedal::~GasPedal()
{

}

void GasPedal::resize(qreal xpos, qreal ypos)
{
    setPos(xpos +438, ypos+ 215);
    setScale(SCALE_FACTOR);
}

void GasPedal::update(int value)
{

}

