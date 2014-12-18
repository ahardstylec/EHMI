#ifndef GASPEDALSPECIAL_H
#define GASPEDALSPECIAL_H

#include <QObject>
#include "gaspedal.h"

class GasPedalSpecial : public GasPedal
{
    Q_OBJECT
public:
    GasPedalSpecial();
    ~GasPedalSpecial();

    void resize(qreal xpos, qreal ypos);
public slots:
    void update(qreal value);
};

#endif // GASPEDALSPECIAL_H
