#include "blinkerspecial.h"

BlinkerSpecial::BlinkerSpecial(qreal x , qreal y, int side) :
    Blinker(side == BLINKER_LEFT ? "data/bilder/special-blinker_left.svg" : "data/bilder/special-blinker_right.svg", x,y, side)
{

}

BlinkerSpecial::~BlinkerSpecial()
{

}

void BlinkerSpecial::resize(qreal xpos, qreal ypos)
{
    setPos(xpos +this->xPosOffset, ypos+ this->yPosOffset);
    setScale(0.4);
}



