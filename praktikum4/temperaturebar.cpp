#include "temperaturebar.h"
#include "global.h"
#include <QGraphicsSvgItem>
#include <QDebug>
#include <math.h>

TemperatureBar::TemperatureBar() : QGraphicsSvgItem("data/bilder/normal-temperature.svg")
{
    originalHeight= this->boundingRect().height();
    originalWidth = this->boundingRect().width();

    qDebug() << "originalHeight" << originalHeight<<endl;
    qDebug() << "originalWidth" << originalWidth<<endl;
    xpos;
    ypos;
}

void TemperatureBar::resize(qreal xpos, qreal ypos)
{
    this->xpos = xpos;
    this->ypos = ypos;
//    setPos(xpos + 265 , ypos + 55 );
    setPos(xpos + 378 , ypos + 145 );
    setScale(SCALE_FACTOR);
}

void TemperatureBar::update(qreal value)
{
//    if (value > max || value < min )return ;
//    qreal newscale = value/(max/100)/100;

////    transform.translate();
//    this->transform().scale(0.5, .5);
//    this->setTransform(this->transform());
}
