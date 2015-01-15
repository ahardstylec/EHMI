#ifndef QSVGVIEW_H
#define QSVGVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include "mainwindow.h"
#include "staticviewnormal.h"
#include "staticviewspecial.h"
#include "temperaturebarnormal.h"
#include "steeringwheelnormal.h"
#include "blinkernormal.h"
#include "gaspedalnormal.h"
#include "speedneedlenormal.h"
#include "rpmneedlenormal.h"
#include "temperaturebarspecial.h"
#include "steeringwheelspecial.h"
#include "blinkerspecial.h"
#include "gaspedalspecial.h"
#include "speedneedlespecial.h"
#include "rpmneedlespecial.h"
#include "global.h"

class QSvgView : public QGraphicsView {
    Q_OBJECT
public:
    QSvgView(QWidget * parent);
    ~QSvgView();

    void loadStaticBackground(const QString &filename);

    TemperatureBar * getTemperatureBarPtr();
    SteeringWheel *getSteeringWheelPtr();
    Blinker *getBlinkerRightPtr();
    Blinker *getBlinkerLeftPtr();
    GasPedal * getGasPedalPtr();
    SpeedNeedle * getSpeedNeedlePtr();
    RpmNeedle * getRpmNeedlePtr();
    mode modus;

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QGraphicsSvgItem * mStaticBackgroundPtr;

    void loadImage(QGraphicsSvgItem **svgItemPtr, const QString &filename);
    void ChangeToNormalMode();
    void ChangeToSpecialMode();
    void reset_pointers();
    void addItemsToScene(int modus);

    TemperatureBar * mTemperatureBarPtr;
    SteeringWheel * mSteeringWheelPtr;
    Blinker * mBlinkerRightPtr;
    Blinker * mBlinkerLeftPtr;
    GasPedal * mGasPedalPtr;
    SpeedNeedle * mSpeedNeedlePtr;
    RpmNeedle *mRpmNeedlePtr;
    StaticView * mStaticViewPtr;
public slots:
    void changeMode(int modus);
};

#endif // QSVGVIEW_H
