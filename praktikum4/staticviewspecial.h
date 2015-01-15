#ifndef STATICVIEWSPECIAL_H
#define STATICVIEWSPECIAL_H

#include <QObject>
#include "staticview.h"

class StaticViewSpecial : public StaticView
{
    Q_OBJECT
public:
    StaticViewSpecial();
    ~StaticViewSpecial();

    void resize(qreal xpos, qreal ypos);
};

#endif // STATICVIEWSPECIAL_H
