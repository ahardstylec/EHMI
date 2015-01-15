#include "speedneedle.h"

SpeedNeedle::SpeedNeedle(QString filename, qreal xPosOffset, qreal yPosOffset) :
        QSvgViewItem(filename, xPosOffset, yPosOffset)
{
}

SpeedNeedle::~SpeedNeedle()
{
}
