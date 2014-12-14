#ifndef BLINKERRIGHT_H
#define BLINKERRIGHT_H


#include <QObject>
#include <QTimer>
#include <QGraphicsSvgItem>

class Blinker : public QGraphicsSvgItem
{
    Q_OBJECT
public:
    Blinker(QString filename, qreal xpos, qreal ypos, int side);
    ~Blinker();
    qreal xpos;
    qreal ypos;
    int side;
    void resize(qreal xpos, qreal ypos);
    QTimer timer;
signals:

public slots:
    void update(int value);
    void toggleVisibility();
};

#endif // BLINKERRIGHT_H
