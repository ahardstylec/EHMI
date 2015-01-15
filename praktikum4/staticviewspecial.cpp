#include "staticviewspecial.h"

StaticViewSpecial::StaticViewSpecial() :
    StaticView("data/bilder/special-static.svg", 180,53)
{

}

StaticViewSpecial::~StaticViewSpecial()
{

}

void StaticViewSpecial::resize(qreal xpos, qreal ypos)
{
    setPos(xpos+ this->xPosOffset, ypos + this->yPosOffset);
    setScale(0.077);
}

