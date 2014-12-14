#include "blinker.h"
#include "global.h"

Blinker::Blinker(QString filename, qreal xpos, qreal ypos, int side) : QGraphicsSvgItem(filename)
{
    this->xpos= xpos;
    this->ypos= ypos;
    this->side= side;
    this->setVisible(false);
    connect(&this->timer, SIGNAL(timeout()), this, SLOT(toggleVisibility()));
}

Blinker::~Blinker()
{

}

void Blinker::toggleVisibility(){
    this->setVisible(!this->isVisible());
}

void Blinker::resize(qreal xpos, qreal ypos)
{
    setPos(xpos +this->xpos, ypos+ this->ypos);
    setScale(SCALE_FACTOR);
}

void Blinker::update(int value)
{
    if(this->side == value){
        this->timer.start(500);
    }else{
        this->timer.stop();
        this->setVisible(false);
    }
}
