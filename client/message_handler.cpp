#include <QDateTime>
#include <QTextCodec>
#include <QThread>

#include <iostream>

#include "message_handler.h"

void threadedMessageOutput(QtMsgType type,
						   const QMessageLogContext &context,
						   const QString &msg)
{
	Q_UNUSED (context);

	QString threadName = QThread::currentThread()->objectName();
	static int index = 0;
	if (threadName.isEmpty())
	{
		threadName = QString("thread #%1").arg(index++);
		QThread::currentThread()->setObjectName(threadName);
	}

	QDateTime time = QDateTime::currentDateTime();
	QString logMsg = time.toString("yyyy-MM-dd HH:mm:ss.zzz");

	switch (type)
	{
	case QtDebugMsg:
		logMsg += " [D] ";
		break;
	case QtWarningMsg:
		logMsg += " [W] ";
		break;
	case QtCriticalMsg:
		logMsg += " [C] ";
		break;
	case QtFatalMsg:
		logMsg += " [F] ";
		break;
	default:
		break;
	}

	logMsg += QString(" [%1] %2").arg(threadName, msg);
	std::cerr << logMsg.toStdString() << std::endl;
}
