#include "blinkernormal.h"

BlinkerNormal::BlinkerNormal(int side)
{
    QString path;
    qreal x,y;
    if(side == BLINKER_LEFT){
        path = "data/bilder/normal-blinker-left.svg";
        x= 140;
        y= 310;
    }else{
        path = "data/bilder/normal-blinker-right.svg";
        y= 325;
        x= 795;
    }
    Blinker::Blinker(side);
    QSvgViewItem::QSvgViewItem(x,y,path);
}

BlinkerNormal::~BlinkerNormal()
{

}

void Blinker::resize(qreal xpos, qreal ypos)
{
    setPos(xpos +this->xPosOffset, ypos+ this->yPosOffset);
    setScale(SCALE_FACTOR);
}
