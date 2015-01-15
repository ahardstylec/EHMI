#include "blinker.h"
#include <qdebug.h>
#include  <QTime>

Blinker::Blinker(QString filename, qreal xPosOffset, qreal yPosOffset, int side) :
        QSvgViewItem(filename, xPosOffset, yPosOffset)
{
    this->side= side;
    this->isBlinking = false;
    this->setVisible(false);
    connect(&this->timer, SIGNAL(timeout()), this, SLOT(blinkerWatchDog()));
}

Blinker::~Blinker()
{

}

void Blinker::toggleBlinker(){
    static QTimer blinktimer;

    if(this->isBlinking){
        setVisible(!isVisible());
        blinktimer.singleShot(500, this, SLOT(toggleBlinker()));
    }else{
//        qDebug() << "toggleBlinker false hide blinker";
        setVisible(false);
    }
}


void Blinker::blinkerWatchDog(){
    this->timer.stop();
//    qDebug() << "blinkerWatchDog " << "off ";
    this->isBlinking = false;
    setVisible(false);
    setLight(false);
}


void Blinker::update(int value)
{
//    qDebug() << this->time.elapsed() << " me " << this->side << " is blining: " << (value == this->side)<<endl ;
    if(this->side == value){
        if(!this->isBlinking){
            this->isBlinking = true;
            setLight(true);
            this->toggleBlinker();
        }
        this->timer.start(500);
    }
}
