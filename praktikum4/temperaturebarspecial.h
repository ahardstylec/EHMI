#ifndef TEMPERATUREBARSPECIAL_H
#define TEMPERATUREBARSPECIAL_H

#include <QObject>

class TemperatureBarSpecial : public TemperatureBar
{
    Q_OBJECT
public:
    TemperatureBarSpecial();
    ~TemperatureBarSpecial();
    void resize(qreal xpos, qreal ypos);
public slots:
    void update(qreal value);
};

#endif // TEMPERATUREBARSPECIAL_H
