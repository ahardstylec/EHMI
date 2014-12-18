#include "qsvgviewitem.h"

QSvgViewItem::QSvgViewItem(QString filename, qreal xPosOffset, qreal yPosOffset) : QGraphicsView(filename)
{
    this->xPosOffset = xPosOffset;
    this->yPosOffset = yPosOffset;
}

QSvgViewItem::~QSvgViewItem()
{

}
