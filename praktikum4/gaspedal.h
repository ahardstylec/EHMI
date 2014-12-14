#ifndef GASPEDAL_H
#define GASPEDAL_H

#include <QObject>
#include <QGraphicsSvgItem>

class GasPedal : public QGraphicsSvgItem
{
    Q_OBJECT
public:
    GasPedal();
    ~GasPedal();
    void resize(qreal xpos, qreal ypos);

signals:

public slots:
    void update(int value);
};

#endif // GASPEDAL_H
