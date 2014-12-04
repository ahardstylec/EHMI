#ifndef CANTRACEPARSER_H
#define CANTRACEPARSER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QFile>

class CanTraceParser : public QObject
{
    Q_OBJECT

private:
    QTimer *m_Timer;
    QTextStream *m_TextStream;

    void ProcessLine(QString);

    int m_nSpeedOfParsing;
    bool m_bRepeatForever;


public:
    explicit CanTraceParser(QObject *parent = 0);


signals:
    void CANMessage(QString);
    void CANMessage(QByteArray);
    void CANMessage(int _MessageID, QByteArray _Data);

    // Geschwindigkeit
    void Speed(qreal);
    void Speed(QString);

    // Drehzahl
    void RPM(qreal);
    void RPM(QString);

    // Kühlmitteltemperatur
    void Temperature(qreal);
    void Temperature(QString);

    // Lenkradwinkel
    void LenkradWinkel(int);
    void LenkradWinkel(QString);

    // Blinker
    void Blinker(int);
    void Blinker(QString);

    // Pedal in %
    void Pedal(qreal);
    void Pedal(QString);


private slots:
    void Update();


public slots:
    void SetFile(QString);

    void Start();
    void SetTimeout(int);
    void Stop();

    void SetRepeatForever(bool);

};

#endif // CANTRACEPARSER_H
