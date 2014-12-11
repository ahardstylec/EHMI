#ifndef QSVGVIEW_H
#define QSVGVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include "temperaturebar.h"

class QSvgView : public QGraphicsView {
    Q_OBJECT
public:
    QSvgView(QWidget * parent);
    ~QSvgView();

    void loadStaticBackground(const QString &filename);
    void loadStaticView(const QString & filename);

    TemperatureBar * getTemperatureBarPtr();
protected:
    void resizeEvent(QResizeEvent *event);
private:
    QGraphicsSvgItem * mStaticViewPtr;
    QGraphicsSvgItem * mStaticBackgroundPtr;

    void loadImage(QGraphicsSvgItem **svgItemPtr, const QString &filename);

    TemperatureBar * mTemperatureBarPtr;

};

#endif // QSVGVIEW_H
