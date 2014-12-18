#ifndef BLINKERNORMAL_H
#define BLINKERNORMAL_H

#include <QObject>
#include "blinker.h"

class BlinkerNormal : public Blinker
{
    Q_OBJECT
public:
    BlinkerNormal(int side);
    ~BlinkerNormal();

    void resize(qreal xpos, qreal ypos);
public slots:
    void update(int value);
};

#endif // BLINKERNORMAL_H
