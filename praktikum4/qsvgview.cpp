#include "qsvgview.h"
#include "global.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>

QSvgView::QSvgView(QWidget * parent) : QGraphicsView(parent),
    mTemperatureBarPtr(new TemperatureBar())

{
    setScene(new QGraphicsScene(this));
    loadStaticBackground("data/bilder/cluster_rahmen.svg");
    loadStaticView("data/bilder/normal-static.svg");
    scene()->addItem(mTemperatureBarPtr);
}

QSvgView::~QSvgView()
{
    if (mStaticViewPtr) delete mStaticViewPtr;

    if (mTemperatureBarPtr) delete mTemperatureBarPtr;
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


void QSvgView::resizeEvent(QResizeEvent * event)
{
    QRectF backgroundRect = mStaticBackgroundPtr->boundingRect();
    scene()->setSceneRect(backgroundRect);
    fitInView(mStaticBackgroundPtr, Qt::KeepAspectRatio);

    mStaticViewPtr->setPos(backgroundRect.x() + 450 * SCALE_FACTOR, backgroundRect.y() + 230 * SCALE_FACTOR);
    mStaticViewPtr->setScale(SCALE_FACTOR);

    // temperaturen bar position
    mTemperatureBarPtr->resize(backgroundRect.x(), backgroundRect.y());

}

