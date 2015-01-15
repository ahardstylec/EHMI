#include "steeringwheel.h"

SteeringWheel::SteeringWheel(QString filename, qreal xPosOffset, qreal yPosOffset) :
        QSvgViewItem(filename, xPosOffset, yPosOffset)
{
}

SteeringWheel::~SteeringWheel()
{

}
