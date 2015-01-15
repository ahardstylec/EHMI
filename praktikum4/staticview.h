#ifndef STATICVIEW_H
#define STATICVIEW_H

#include <QObject>
#include <QDebug>
#include "qsvgviewitem.h"

class StaticView : public QSvgViewItem
{
    Q_OBJECT
public:
    StaticView(QString filename, qreal xPosOffset, qreal yPosOffset);
    ~StaticView();

};

#endif // STATICVIEW_H
