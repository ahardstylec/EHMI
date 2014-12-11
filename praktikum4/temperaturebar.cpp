#include "temperaturebar.h"
#include "global.h"
#include <QGraphicsSvgItem>
#include <QDebug>

TemperatureBar::TemperatureBar() : QGraphicsSvgItem("data/bilder/normal-temperature.svg")
{
}

void TemperatureBar::resize(qreal xpos, qreal ypos)
{
    setPos(xpos + 910 * SCALE_FACTOR, ypos + 200 * SCALE_FACTOR);
    setScale(SCALE_FACTOR);
}

void TemperatureBar::update(qreal value)
{

}

