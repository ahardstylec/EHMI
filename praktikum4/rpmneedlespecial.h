#ifndef RPMNEEDLESPECIAL_H
#define RPMNEEDLESPECIAL_H

#include <QObject>
#include "rpmneedle.h"

class RpmNeedleSpecial : public RpmNeedle
{
    Q_OBJECT
public:
    RpmNeedleSpecial();
    ~RpmNeedleSpecial();
    void resize(qreal xpos, qreal ypos);

public slots:
    void update(qreal value);
};

#endif // RPMNEEDLESPECIAL_H
