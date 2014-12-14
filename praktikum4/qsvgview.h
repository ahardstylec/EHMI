#ifndef QSVGVIEW_H
#define QSVGVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include "temperaturebar.h"
#include "steeringwheel.h"
#include "blinker.h"
#include "gaspedal.h"

class QSvgView : public QGraphicsView {
    Q_OBJECT
public:
    QSvgView(QWidget * parent);
    ~QSvgView();

    void loadStaticBackground(const QString &filename);
    void loadStaticView(const QString & filename);

    TemperatureBar * getTemperatureBarPtr();
    SteeringWheel *getSteeringWheelPtr();
    Blinker *getBlinkerRightPtr();
    Blinker *getBlinkerLeftPtr();
    GasPedal * getGasPedalPtr();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QGraphicsSvgItem * mStaticViewPtr;
    QGraphicsSvgItem * mStaticBackgroundPtr;

    void loadImage(QGraphicsSvgItem **svgItemPtr, const QString &filename);

    TemperatureBar * mTemperatureBarPtr;
    SteeringWheel * mSteeringWheelPtr;
    Blinker * mBlinkerRightPtr;
    Blinker * mBlinkerLeftPtr;
    GasPedal * mGasPedalPtr;

};

#endif // QSVGVIEW_H
