#ifndef BLINKERSPECIAL_H
#define BLINKERSPECIAL_H

#include <QObject>
#include "blinker.h"

class BlinkerSpecial : public Blinker
{
    Q_OBJECT
public:
    BlinkerSpecial(int side);
    ~BlinkerSpecial();
    void resize(qreal xpos, qreal ypos);
public slots:
    void update(int value);
};

#endif // BLINKERSPECIAL_H
