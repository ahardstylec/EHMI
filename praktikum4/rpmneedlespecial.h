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

    QGraphicsSvgItem * tempTwo;
    QGraphicsSvgItem * tempThree;
    QGraphicsSvgItem * tempFour;
    QGraphicsSvgItem * getTempThreePtr();
    QGraphicsSvgItem * getTempTwoPtr();
    QGraphicsSvgItem * getTempFourPtr();

public slots:
    void update(qreal value);
private:
    void initResize(QGraphicsSvgItem* item, qreal xpos, qreal ypos);
};

#endif // RPMNEEDLESPECIAL_H
