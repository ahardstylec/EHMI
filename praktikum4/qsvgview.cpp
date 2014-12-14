#include "qsvgview.h"
#include "global.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>

QSvgView::QSvgView(QWidget * parent) : QGraphicsView(parent),
    mTemperatureBarPtr(new TemperatureBar()),
    mSteeringWheelPtr(new SteeringWheel()),
    mBlinkerLeftPtr(new Blinker("data/bilder/normal-blinker_left.svg", 140, 310, 1)),
    mBlinkerRightPtr(new Blinker("data/bilder/normal-blinker_right.svg", 795, 325, -1)),
    mGasPedalPtr(new GasPedal())

{
    setScene(new QGraphicsScene(this));
    loadStaticBackground("data/bilder/cluster_rahmen.svg");
    loadStaticView("data/bilder/normal-static.svg");
    scene()->addItem(mTemperatureBarPtr);
    scene()->addItem(mSteeringWheelPtr);
    scene()->addItem(mBlinkerLeftPtr);
    scene()->addItem(mBlinkerRightPtr);
    scene()->addItem(mGasPedalPtr);
}

QSvgView::~QSvgView()
{
    if (mStaticViewPtr) delete mStaticViewPtr;
    if (mTemperatureBarPtr) delete mTemperatureBarPtr;
    if (mSteeringWheelPtr) delete mSteeringWheelPtr;
    if (mBlinkerLeftPtr) delete mBlinkerLeftPtr;
    if (mBlinkerRightPtr) delete mBlinkerRightPtr;
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

}

