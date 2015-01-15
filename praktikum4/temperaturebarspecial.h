#ifndef TEMPERATUREBARSPECIAL_H
#define TEMPERATUREBARSPECIAL_H

#include <QObject>
#include <QVector3D>
#include "temperaturebar.h"

class TemperatureBarSpecial : public TemperatureBar
{
    Q_OBJECT
public:
    TemperatureBarSpecial();
    ~TemperatureBarSpecial();
    void resize(qreal xpos, qreal ypos);
    QVector3D rotationPoint;
public slots:
    void update(qreal value);
};

#endif // TEMPERATUREBARSPECIAL_H
