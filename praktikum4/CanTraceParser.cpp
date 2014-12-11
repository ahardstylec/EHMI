#include "CanTraceParser.h"
#include <QString>
#include <QStringList>
#include <QBitArray>

CanTraceParser::CanTraceParser(QObject *parent) :
    QObject(parent),
    m_TextStream(0),
    m_nSpeedOfParsing(20)
{
    m_Timer = new QTimer(this);

    QObject::connect(m_Timer, SIGNAL(timeout()), this, SLOT(Update()));
}


void CanTraceParser::SetFile(QString myFileName)
{
    qDebug() << "Set File with Param: " << myFileName << endl;

    QFile* file = new QFile(myFileName);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    if(m_TextStream!=0)
    { delete m_TextStream; }

    m_TextStream = new QTextStream(file);

}


void CanTraceParser::Start()
{
    qDebug() << "Thread Name: " << this->thread()->objectName() << " --> Start" << endl;

    if(m_Timer->isActive())
        m_Timer->stop();

    m_Timer->start(m_nSpeedOfParsing);
}


void CanTraceParser::SetTimeout(int pos)
{
    qDebug() << "Set Timeout to: " << pos << endl;
    m_nSpeedOfParsing = qMax(pos,10);
}


void CanTraceParser::Stop()
{
    qDebug() << "Stop " << endl;

    m_Timer->stop();
}


void CanTraceParser::SetRepeatForever(bool repeat)
{
    qDebug() << "Repeat Forever is set to " << repeat << endl;

    m_bRepeatForever = repeat;
}

void CanTraceParser::setTime(int position)
{
    qDebug() << "change time position "<< position<< endl;
    if(m_Timer->isActive())
        m_Timer->stop();
    m_TextStream->seek(position*64);
    m_Timer->start();
}



void CanTraceParser::ProcessLine(QString _Line)
{
    // Beispiel mit Geschwindigkeit
    // ===> 0.138200 1 100 Rx d 8 83 E8 BF FF 00 00 00 80
    //
    // Nachricht auswerten:
    // 83        E8        BF        FF        00        00        00        80
    // 1000 0011 1110 0011 1011 1111 1111 1111 0000 0000 0000 0000 0000 0000 1000 0000
    //
    // BYTE ORDER
    // 80        00        00        00        FF        BF        E8        83
    // 1000 0000 0000 0000 0000 0000 0000 0000 1111 1111 1011 1111 1110 1000 1000 0011
    //                     |<Geschwindigkeit>|
    //                     0 * 0,01 + 0 = 0
    //

    QStringList myMessageParts = _Line.split(QChar(' '), QString::SkipEmptyParts);

    if(myMessageParts.length()>=3 && !myMessageParts.at(2).isEmpty() )
    {
        int nMessageID = myMessageParts.at(2).toInt(0,16);

        // Parse CAN Message
        int nFieldWithLetterD = myMessageParts.indexOf("d");

        QString myHexMessage("0x");
        for(int i=myMessageParts.length()-1; i > nFieldWithLetterD+1; i--)
        {
            myHexMessage.append(myMessageParts.at(i));
        }

        bool bConvertOK = false;
        quint64 myCANMessageContainer = myHexMessage.toULongLong(&bConvertOK, 16);

        if(!bConvertOK)
        { return; }


        // Byte Array
        QByteArray myByteArray;
        myByteArray.append(nMessageID);
        myByteArray.append(myCANMessageContainer);

        // Standard Message
        emit( CANMessage(myByteArray) ); // Als Byte Array
        emit( CANMessage( QString("{\"ID\":\"%1\",\"Data\":\"%2\"}").arg(nMessageID).arg(myHexMessage) ) ); // JSON format (see http://json.org/ for references)

        // Message IDs specific
        switch(nMessageID)
        {
            // SPEED
            case 256:
            {            
                // Get actual value
                qreal mySpeed = (myCANMessageContainer & 0xFFFF00000000) >> 32;

                // Ok use the formula to calculate the real physical value
                mySpeed = mySpeed * 0.01 + 0;

                if(mySpeed>=0)
                {
                    emit Speed(mySpeed);
                    emit Speed(QString("%1").arg(mySpeed,10));
                }
            }
            break;


            // RPM (Drehzahl & Pedal)
            case 261:
            {
                // Get actual value
                qreal myRPM = (myCANMessageContainer & 0xFFFF0000) >> 16;

                // Ok use the formula to calculate the real physical value
                myRPM = myRPM * 0.25 + 0;


                // Get actual value
                qreal myPedal = (myCANMessageContainer & 0xFF000000000000) >> 48;

                // Ok use the formula to calculate the real physical value
                myPedal = myPedal * 0.4 + 0;

                // Send Signals
                emit RPM(myRPM);
                emit RPM(QString("%1").arg(myRPM,10));
                emit Pedal(myPedal);
                emit Pedal(QString("%1").arg(myPedal,10));
            }
            break;


            // Temperature
            case 1600:
            {
                // Get actual value
                qreal myTemperature = (qreal)((myCANMessageContainer & 0xFF000000) >> 24);

                // Ok use the formula to calculate the real physical value
                myTemperature = myTemperature * 0.75 + -48;

                // Send Signals
                emit Temperature(myTemperature);
                emit Temperature(QString("%1").arg(myTemperature,10));
            }
            break;


            // Lenkradwinkel
            case 134:
            {
                // Vorzeichen
                int myVorzeichen = (int)((myCANMessageContainer & 0x20000000) >> 29);

                // Eigentlicher Wert
                qreal myWinkel = (qreal)((myCANMessageContainer & 0x1FFF0000) >> 16);

                // Richtiger Wert
                myWinkel = myWinkel * 0.1 + 0;

                // Vorzeichen anf�gen
                if(myVorzeichen==1)
                {
                   myWinkel *= -1;
                }

                // Send Signals
                emit LenkradWinkel((int)myWinkel);
                emit LenkradWinkel(QString("%1").arg(myWinkel,10));
            }
            break;


            // Blinker
            case 867:
            {
                // Get actual value
                int myBlinkerRechts = (int)((myCANMessageContainer & 0x200) >> 9);
                int myBlinkerLinks = (int)((myCANMessageContainer & 0x100) >> 8);

                // Send Signals...
                if(myBlinkerRechts>0)
                {
                    emit Blinker("rechts");
                    emit Blinker(1);
                }
                if(myBlinkerLinks>0)
                {
                    emit Blinker("links");
                    emit Blinker(-1);
                }
            }
            break;

            default:
            {

            }
            break;
        }
    }



}




void CanTraceParser::Update()
{
    if(m_TextStream)
    {
        int i=0;
        while(!m_TextStream->atEnd() && i < 10)
        {
            QString line = m_TextStream->readLine();

            ProcessLine(line);

            i++;
        }

        if(m_TextStream->atEnd() && m_bRepeatForever)
        {
            bool retValue = m_TextStream->seek(0);
            qDebug() << "Restart CAN-Trace: " << retValue << endl;
        }
    }
}
