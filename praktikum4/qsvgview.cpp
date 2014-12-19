#include "qsvgview.h"
#include "global.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>

QSvgView::QSvgView(QWidget * parent) : QGraphicsView(parent),
    mTemperatureBarPtr(new TemperatureBarNormal()),
    mSteeringWheelPtr(new SteeringWheelNormal()),
    mBlinkerLeftPtr(new BlinkerNormal(BLINKER_LEFT)),
    mBlinkerRightPtr(new BlinkerNormal(BLINKER_RIGHT)),
    mGasPedalPtr(new GasPedalNormal()),
    mSpeedNeedlePtr(new SpeedNeedleNormal()),
    mRpmNeedlePtr(new RpmNeedleNormal())
{
    setScene(new QGraphicsScene(this));
    loadStaticBackground("data/bilder/cluster_rahmen.svg");
    loadStaticView("data/bilder/normal-static.svg");
    scene()->addItem(mTemperatureBarPtr);
    scene()->addItem(mSteeringWheelPtr);
    scene()->addItem(mBlinkerLeftPtr);
    scene()->addItem(mBlinkerRightPtr);
    scene()->addItem(mGasPedalPtr);
    scene()->addItem(mSpeedNeedlePtr);
    scene()->addItem(mRpmNeedlePtr);
}

QSvgView::~QSvgView()
{
    if (mStaticViewPtr) delete mStaticViewPtr;
    if (mTemperatureBarPtr) delete mTemperatureBarPtr;
    if (mSteeringWheelPtr) delete mSteeringWheelPtr;
    if (mBlinkerLeftPtr) delete mBlinkerLeftPtr;
    if (mBlinkerRightPtr) delete mBlinkerRightPtr;
    if (mGasPedalPtr) delete mGasPedalPtr;
    if (mSpeedNeedlePtr) delete mSpeedNeedlePtr;
    if (mRpmNeedlePtr) delete mRpmNeedlePtr;
}

void QSvgView::loadImage(QGraphicsSvgItem ** svgItemPtr, const QString & filename)
{
    *svgItemPtr = new QGraphicsSvgItem(filename);
    if (*svgItemPtr == NULL) {
        qDebug() << "could not load file \"" << filename << "\"";
    }
    scene()->addItem(*svgItemPtr);
}

void QSvgView::loadStaticBackground(const QString & filename)
{
    loadImage(&mStaticBackgroundPtr, filename);

}

void QSvgView::loadStaticView(const QString & filename)
{
    loadImage(&mStaticViewPtr, filename);

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

    mStaticViewPtr->setPos(backgroundRect.x() + 450 * SCALE_FACTOR, backgroundRect.y() + 230 * SCALE_FACTOR);
    mStaticViewPtr->setScale(SCALE_FACTOR);

    // temperaturen bar position
    mTemperatureBarPtr->resize(backgroundRect.x(), backgroundRect.y());
    mSteeringWheelPtr->resize(backgroundRect.x(), backgroundRect.y());
    mBlinkerLeftPtr->resize(backgroundRect.x(), backgroundRect.y());
    mBlinkerRightPtr->resize(backgroundRect.x(), backgroundRect.y());
    mGasPedalPtr->resize(backgroundRect.x(), backgroundRect.y());
    mSpeedNeedlePtr->resize(backgroundRect.x(), backgroundRect.y());
    mRpmNeedlePtr->resize(backgroundRect.x(), backgroundRect.y());
}

