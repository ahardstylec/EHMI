#include "gaspedal.h"

GasPedal::GasPedal(QString filename, qreal xPosOffset, qreal yPosOffset) :
        QSvgViewItem(filename, xPosOffset, yPosOffset)
{
}

GasPedal::~GasPedal()
{
}
