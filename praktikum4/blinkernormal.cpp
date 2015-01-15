#include "blinkernormal.h"

BlinkerNormal::BlinkerNormal(qreal x , qreal y, int side) :
    Blinker(((side == BLINKER_LEFT) ? "data/bilder/normal-blinker_left.svg" : "data/bilder/normal-blinker_right.svg"), x, y,  side)
{
}

BlinkerNormal::~BlinkerNormal()
{

}

void BlinkerNormal::resize(qreal xpos, qreal ypos)
{
    setPos(xpos +this->xPosOffset, ypos+ this->yPosOffset);
    setScale(SCALE_FACTOR);
}

