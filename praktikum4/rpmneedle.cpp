#include "rpmneedle.h"
#include "global.h"

RpmNeedle::RpmNeedle(QString filename, qreal xPosOffset, qreal yPosOffset) :
        QSvgViewItem(filename, xPosOffset, yPosOffset)
{

}

RpmNeedle::~RpmNeedle()
{

}
