#include "staticviewnormal.h"

StaticViewNormal::StaticViewNormal() :
    StaticView("data/bilder/normal-static.svg",450,230)
{

}

StaticViewNormal::~StaticViewNormal()
{

}



void StaticViewNormal::resize(qreal xpos, qreal ypos)
{
    setPos(xpos+ this->xPosOffset * SCALE_FACTOR, ypos + this->yPosOffset * SCALE_FACTOR);
    setScale(SCALE_FACTOR);
}
