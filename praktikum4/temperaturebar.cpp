#include "temperaturebar.h"

TemperatureBar::TemperatureBar(QString filename, qreal xPosOffset, qreal yPosOffset) :
    QSvgViewItem(filename, xPosOffset, yPosOffset)
{
}

TemperatureBar::~TemperatureBar()
{

}
