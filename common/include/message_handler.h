#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <QDebug>

// message output to replace standard Qt handler with timestamps
// and threads info
void threadedMessageOutput(QtMsgType type,
						   const QMessageLogContext &context,
						   const QString &msg);

#endif // MESSAGE_HANDLER_H
