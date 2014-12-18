#include "temperaturebarspecial.h"

TemperatureBarSpecial::TemperatureBarSpecial() :
    TemperatureBar(),
    QSvgViewItem("data/bilder/special-temperaturebar.svg", 0,0)
{

}

TemperatureBarSpecial::~TemperatureBarSpecial()
{

}

void TemperatureBarNormal::resize(qreal xpos, qreal ypos)
{
    setPos(xpos + xPosOffset , ypos + yPosOffset );
    setScale(SCALE_FACTOR);
}

void TemperatureBarNormal::update(qreal value)
{

}
