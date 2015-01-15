#include "staticview.h"

StaticView::StaticView(QString filename, qreal xPosOffset, qreal yPosOffset) :
            QSvgViewItem(filename, xPosOffset, yPosOffset)
{

}

StaticView::~StaticView()
{

}

