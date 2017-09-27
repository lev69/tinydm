#include <QApplication>
#include <QMainWindow>
#include <QTimer>

#include <controller.h>

//#include <iostream>
//#include <rest_client.h>
#include <message_handler.h>

int main(int argc, char **argv)
{
	qInstallMessageHandler(threadedMessageOutput);
	QApplication app(argc, argv);
	Controller ctl;
	QTimer::singleShot(0, &ctl, &Controller::init);
	return app.exec();

//	RestClient::Options opt;
//	opt.schema = "http";
//	opt.host = "localhost";
//	opt.port = 80;
//	opt.path = "/api";

//	RestClient cli(opt);
//	std::list<DiskInfo> diskList;
//	try
//	{
//		 diskList = cli.getDiskInfo();
//	}
//	catch (const std::exception &e)
//	{
//		cerr << "Error: " << e.what() << endl;
//	}

//	for_each (diskList.begin(), diskList.end(), [](DiskInfo &disk)
//	{
//		std::cout << disk << std::endl;
//	});



	return 0;
}
