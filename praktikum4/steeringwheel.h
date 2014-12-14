#ifndef STEERINGWHEEL_H
#define STEERINGWHEEL_H

#include <QObject>
#include <QGraphicsSvgItem>

class SteeringWheel : public QGraphicsSvgItem
{
    Q_OBJECT
public:
    SteeringWheel();
    ~SteeringWheel();

    void resize(qreal xpos, qreal ypos);
signals:

public slots:
    void update(qreal value);
};

#endif // STEERINGWHEEL_H
