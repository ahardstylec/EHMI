#ifndef GASPEDALNORMAL_H
#define GASPEDALNORMAL_H

#include <QObject>
#include "gaspedal.h"

class GasPedalNormal : public GasPedal
{
public:
    GasPedalNormal();
    ~GasPedalNormal();

    void resize(qreal xpos, qreal ypos);
public slots:
    void update(qreal value);
};

#endif // GASPEDALNORMAL_H
