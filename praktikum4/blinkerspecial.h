#ifndef BLINKERSPECIAL_H
#define BLINKERSPECIAL_H

#include <QObject>
#include "blinker.h"

class BlinkerSpecial : public Blinker
{
    Q_OBJECT
public:
    BlinkerSpecial(qreal, qreal, int side);
    ~BlinkerSpecial();
    void resize(qreal xpos, qreal ypos);
};

#endif // BLINKERSPECIAL_H
