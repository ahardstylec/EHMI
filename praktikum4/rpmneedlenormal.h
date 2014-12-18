#ifndef RPMNEEDLENORMAL_H
#define RPMNEEDLENORMAL_H

#include <QObject>
#include "rpmneedle.h"

class RpmNeedleNormal : public RpmNeedle
{
    Q_OBJECT
public:
    RpmNeedleNormal();
    ~RpmNeedleNormal();
    void resize(qreal xpos, qreal ypos);
public slots:
    void update(qreal value);
};

#endif // RPMNEEDLENORMAL_H
