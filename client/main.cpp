#include <QApplication>
#include <QTimer>

#include <controller.h>
#include <message_handler.h>

int main(int argc, char **argv)
{
	qInstallMessageHandler(threadedMessageOutput);
	QApplication app(argc, argv);
	Controller ctl;
	QTimer::singleShot(0, &ctl, &Controller::init);
	return app.exec();
}
