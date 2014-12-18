#ifndef SPEEDNEEDLESPECIAL_H
#define SPEEDNEEDLESPECIAL_H

#include <QObject>
#include "speedneedle.h"

class SpeedNeedleSpecial : public SpeedNeedle
{
    Q_OBJECT
public:
    SpeedNeedleSpecial();
    ~SpeedNeedleSpecial();
    void resize(qreal xpos, qreal ypos);
public slots:
    void update(qreal value);
};

#endif // SPEEDNEEDLESPECIAL_H
