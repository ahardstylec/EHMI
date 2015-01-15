#ifndef STEERINGWHEEL_H
#define STEERINGWHEEL_H

#include <QObject>
#include "qsvgviewitem.h"

class SteeringWheel : public QSvgViewItem
{
    Q_OBJECT
public:
    SteeringWheel(QString filename, qreal xPosOffset, qreal yPosOffset);
    ~SteeringWheel();

public slots:
    virtual void update(int value)=0;
};

#endif // STEERINGWHEEL_H
