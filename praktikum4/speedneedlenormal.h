#ifndef SPEEDNEEDLENORMAL_H
#define SPEEDNEEDLENORMAL_H

#include <QObject>
#include "speedneedle.h"

class SpeedNeedleNormal : public SpeedNeedle
{
    Q_OBJECT
public:
    SpeedNeedleNormal();
    ~SpeedNeedleNormal();
    void resize(qreal xpos, qreal ypos);
public slots:
    void update(qreal value);
};

#endif // SPEEDNEEDLENORMAL_H
