#ifndef STATIVVIEWNORMAL_H
#define STATIVVIEWNORMAL_H

#include <QObject>
#include "staticview.h"

class StaticViewNormal : public StaticView
{
    Q_OBJECT
public:
    StaticViewNormal();
    ~StaticViewNormal();

    void resize(qreal xpos, qreal ypos);
};

#endif // STATIVVIEWNORMAL_H
