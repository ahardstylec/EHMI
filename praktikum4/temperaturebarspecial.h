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
    qreal originalHeight;
    qreal originalWidth;
    QGraphicsSvgItem * tempTwo;
    QGraphicsSvgItem * tempThree;
    QGraphicsSvgItem * getTempThreePtr();
    QGraphicsSvgItem * getTempTwoPtr();
    QVector3D rotationPoint;
public slots:
    void update(qreal value);

private:
    void initResize(QGraphicsSvgItem *, qreal xpos, qreal ypos);
};

#endif // TEMPERATUREBARSPECIAL_H
