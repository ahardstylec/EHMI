#ifndef BLINKERNORMAL_H
#define BLINKERNORMAL_H

#include <QObject>
#include "blinker.h"

class BlinkerNormal : public Blinker
{
    Q_OBJECT
public:
    BlinkerNormal(qreal x, qreal y, int side);
    ~BlinkerNormal();

    void resize(qreal xpos, qreal ypos);
};

#endif // BLINKERNORMAL_H
