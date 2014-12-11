#ifndef TEMPERATUREBAR_H
#define TEMPERATUREBAR_H

#include <QObject>
#include <QGraphicsSvgItem>

class TemperatureBar : public QGraphicsSvgItem
{
    Q_OBJECT
public:
    TemperatureBar();
    void resize(qreal xpos, qreal ypos);
signals:

public slots:
    void update(qreal value);


private:
  //  const QString mImageFile = "data/bilder/normal-temperature.svg";

};

#endif // TEMPERATUREBAR_H
