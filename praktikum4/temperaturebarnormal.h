#ifndef TEMPERATUREBARNORMAL_H
#define TEMPERATUREBARNORMAL_H

#include <QObject>
#include "temperaturebar.h"

class TemperatureBarNormal : public TemperatureBar
{
    Q_OBJECT
public:
    TemperatureBarNormal();
    ~TemperatureBarNormal();
private:
    qreal originalHeight;

    void resize(qreal xpos, qreal ypos);

public slots:
    void update(qreal value);
};

#endif // TEMPERATUREBARNORMAL_H
