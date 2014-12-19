#ifndef QSVGVIEWITEM_H
#define QSVGVIEWITEM_H

#include <QObject>
#include <QGraphicsSvgItem>
#include "global.h"

class QSvgViewItem : public QGraphicsSvgItem
{
    Q_OBJECT
public:
    QSvgViewItem(QString filename, qreal xPosOffset, qreal yPosOffset);
    ~QSvgViewItem();

    virtual void resize(qreal xpos, qreal ypos)= 0;
};

#endif // QSVGVIEWITEM_H
