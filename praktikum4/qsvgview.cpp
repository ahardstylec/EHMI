#include "qsvgview.h"
#include "global.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>

QSvgView::QSvgView(QWidget * parent) : QGraphicsView(parent),
    mTemperatureBarPtr(new TemperatureBarNormal()),
    mSteeringWheelPtr(new SteeringWheelNormal()),
    mBlinkerLeftPtr(new BlinkerNormal(140, 310,BLINKER_LEFT)),
    mBlinkerRightPtr(new BlinkerNormal(795, 325,BLINKER_RIGHT)),
    mGasPedalPtr(new GasPedalNormal()),
    mSpeedNeedlePtr(new SpeedNeedleNormal()),
    mRpmNeedlePtr(new RpmNeedleNormal()),
    mStaticViewPtr(new StaticViewNormal())
{
    addItemsToScene(1);
}

void QSvgView::changeMode(int modus){
   qDebug() << "Modus " << modus;
   reset_pointers();
   switch(modus){
    case -3:
       mStaticViewPtr = new StaticViewSpecial();
       mTemperatureBarPtr = new TemperatureBarSpecial();
       mSteeringWheelPtr = new SteeringWheelSpecial();
       mBlinkerLeftPtr = new BlinkerSpecial(195, 300, BLINKER_LEFT);
       mBlinkerRightPtr=new BlinkerSpecial(720, 305, BLINKER_RIGHT);
       mGasPedalPtr =new GasPedalSpecial();
       mSpeedNeedlePtr = new SpeedNeedleSpecial();
       mRpmNeedlePtr = new RpmNeedleSpecial();
       break;
    default:
       mStaticViewPtr = new StaticViewNormal();
       mTemperatureBarPtr = new TemperatureBarNormal();
       mSteeringWheelPtr = new SteeringWheelNormal();
       mBlinkerLeftPtr = new BlinkerNormal(140, 310, BLINKER_LEFT);
       mBlinkerRightPtr=new BlinkerNormal(795, 325, BLINKER_RIGHT);
       mGasPedalPtr =new GasPedalNormal();
       mSpeedNeedlePtr = new SpeedNeedleNormal();
       mRpmNeedlePtr = new RpmNeedleNormal();
   }
   addItemsToScene(modus);
}

void QSvgView::addItemsToScene(int modus){
    setScene(new QGraphicsScene(this));
    loadStaticBackground("data/bilder/cluster_rahmen.svg");
    scene()->addItem(mStaticBackgroundPtr);
    scene()->addItem(mStaticViewPtr);
    scene()->addItem(mTemperatureBarPtr);
    if(modus== -3){
        scene()->addItem(((TemperatureBarSpecial *) mTemperatureBarPtr)->getTempTwoPtr());
        scene()->addItem(((TemperatureBarSpecial *) mTemperatureBarPtr)->getTempThreePtr());
    }
    scene()->addItem(mSteeringWheelPtr);
    scene()->addItem(mBlinkerLeftPtr);
    scene()->addItem(mBlinkerRightPtr);
    scene()->addItem(mGasPedalPtr);
    scene()->addItem(mSpeedNeedlePtr);
    scene()->addItem(mRpmNeedlePtr);
    if(modus== -3){
        scene()->addItem(((RpmNeedleSpecial *) mRpmNeedlePtr)->getTempTwoPtr());
        scene()->addItem(((RpmNeedleSpecial *) mRpmNeedlePtr)->getTempThreePtr());
        scene()->addItem(((RpmNeedleSpecial *) mRpmNeedlePtr)->getTempFourPtr());
    }
}

QSvgView::~QSvgView()
{
    reset_pointers();
}

void QSvgView::loadImage(QGraphicsSvgItem ** svgItemPtr, const QString & filename)
{
    *svgItemPtr = new QGraphicsSvgItem(filename);
    if (*svgItemPtr == NULL) {
        qDebug() << "could not load file \"" << filename << "\"";
    }
}

void QSvgView::reset_pointers()
{
    if (mStaticViewPtr) delete mStaticViewPtr;
    if (mTemperatureBarPtr) delete mTemperatureBarPtr;
    if (mSteeringWheelPtr) delete mSteeringWheelPtr;
    if (mBlinkerLeftPtr) delete mBlinkerLeftPtr;
    if (mBlinkerRightPtr) delete mBlinkerRightPtr;
    if (mGasPedalPtr) delete mGasPedalPtr;
    if (mSpeedNeedlePtr) delete mSpeedNeedlePtr;
    if (mRpmNeedlePtr) delete mRpmNeedlePtr;
    if (mStaticBackgroundPtr) delete mStaticBackgroundPtr;
}

void QSvgView::loadStaticBackground(const QString & filename)
{
    loadImage(&mStaticBackgroundPtr, filename);
}

TemperatureBar *QSvgView::getTemperatureBarPtr()
{
    return mTemperatureBarPtr;
}

SteeringWheel * QSvgView::getSteeringWheelPtr(){
    return mSteeringWheelPtr;
}

Blinker * QSvgView::getBlinkerLeftPtr(){
    return mBlinkerLeftPtr;
}

GasPedal *QSvgView::getGasPedalPtr()
{
    return mGasPedalPtr;
}

SpeedNeedle *QSvgView::getSpeedNeedlePtr()
{
    return mSpeedNeedlePtr;
}

RpmNeedle *QSvgView::getRpmNeedlePtr()
{
    return mRpmNeedlePtr;
}

Blinker * QSvgView::getBlinkerRightPtr(){
    return mBlinkerRightPtr;
}


void QSvgView::resizeEvent(QResizeEvent * event)
{
    QRectF backgroundRect = mStaticBackgroundPtr->boundingRect();
    scene()->setSceneRect(backgroundRect);
    fitInView(mStaticBackgroundPtr, Qt::KeepAspectRatio);

    // temperaturen bar position
    mStaticViewPtr->resize(backgroundRect.x(), backgroundRect.y());
    mTemperatureBarPtr->resize(backgroundRect.x(), backgroundRect.y());
    mSteeringWheelPtr->resize(backgroundRect.x(), backgroundRect.y());
    mBlinkerLeftPtr->resize(backgroundRect.x(), backgroundRect.y());
    mBlinkerRightPtr->resize(backgroundRect.x(), backgroundRect.y());
    mGasPedalPtr->resize(backgroundRect.x(), backgroundRect.y());
    mSpeedNeedlePtr->resize(backgroundRect.x(), backgroundRect.y());
    mRpmNeedlePtr->resize(backgroundRect.x(), backgroundRect.y());
}
