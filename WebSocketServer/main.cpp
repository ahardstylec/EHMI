// Example Code copied from https://github.com/ant-lafarge/QtWebsocket

#include "ServerThreaded.h"
#include "CanTraceParser.h"
#include "Log.h"
#include <QApplication>
#include <QTimer>
#include <QDir>



void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	QString msg2;
	//QByteArray localMsg = msg.toLocal8Bit();
	switch (type)
	{
		case QtDebugMsg:
			msg2 = QString("Debug: %1 (%2:%3, %4)\n").arg(msg).arg(context.file).arg(context.line).arg(context.function);
			//fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
			break;
		case QtWarningMsg:
			msg2 = QString("Warning: %1 (%2:%3, %4)\n").arg(msg).arg(context.file).arg(context.line).arg(context.function);
			//fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
			break;
		case QtCriticalMsg:
			msg2 = QString("Critical: %1 (%2:%3, %4)\n").arg(msg).arg(context.file).arg(context.line).arg(context.function);
			//fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
			break;
		case QtFatalMsg:
			msg2 = QString("Fatal: %1 (%2:%3, %4)\n").arg(msg).arg(context.file).arg(context.line).arg(context.function);
			//fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
			abort();
	}

	Log::display(msg2);
}



int main(int argc, char *argv[])
{
	qInstallMessageHandler(myMessageOutput);

	QApplication app(argc, argv);




	ServerThreaded myThreadedServer;


    Log::display();
    Log::display("Path: " + QDir::currentPath());

    Log::display( "main thread : 0x" + QString::number((intptr_t)QThread::currentThreadId(), 16) );
    CanTraceParser myTraceParser;
    myTraceParser.SetFile("./data/Trace.txt");
    myTraceParser.SetRepeatForever(true);
    //QObject::connect( &myTraceParser, SIGNAL(CANMessage(QByteArray)), &myThreadedServer, SLOT(SendBroadcastMessage(QByteArray)) );
    QObject::connect( &myTraceParser, SIGNAL(CANMessage(QString)), &myThreadedServer, SLOT(SendBroadcastMessage(QString)) );
    myTraceParser.Start();


	return app.exec();
}
