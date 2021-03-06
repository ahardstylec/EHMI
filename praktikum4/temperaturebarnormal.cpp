#include "temperaturebarnormal.h"
#include <QDebug>
#include <math.h>
#include <QTransform>
#include "global.h"

TemperatureBarNormal::TemperatureBarNormal() :
    TemperatureBar("data/bilder/normal-temperature.svg", 378 , -133 )
{
    originalHeight= this->boundingRect().height();
    setTransformOriginPoint ( 0, originalHeight );
}

TemperatureBarNormal::~TemperatureBarNormal()
{

}

void TemperatureBarNormal::resize(qreal xpos, qreal ypos)
{
    setPos(xpos + this->xPosOffset , ypos + this->yPosOffset );
    setScale(SCALE_FACTOR);
}

void TemperatureBarNormal::update(qreal value)
{
    qreal newscale = value/120;
    QTransform transform;
    transform.translate(0, originalHeight - originalHeight *newscale);
    transform = transform.scale(1, newscale);
    setTransform(transform);
}
