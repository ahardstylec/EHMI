#include "qsvgviewitem.h"

QSvgViewItem::QSvgViewItem(QString filename, qreal xPosOffset, qreal yPosOffset) : QGraphicsSvgItem(filename)
{
    this->xPosOffset = xPosOffset;
    this->yPosOffset = yPosOffset;
}

QSvgViewItem::QSvgViewItem()
{

}

QSvgViewItem::~QSvgViewItem()
{

}
