#ifndef TEMPERATUREBAR_H
#define TEMPERATUREBAR_H

#include <QObject>
#include "qsvgviewitem.h"

class TemperatureBar : public QSvgViewItem
{
    Q_OBJECT
public:
    TemperatureBar(QString filename, qreal xPosOffset, qreal yPosOffset);
    ~TemperatureBar();

public slots:
    virtual void update(qreal value) = 0;
};

#endif // TEMPERATUREBAR_H
