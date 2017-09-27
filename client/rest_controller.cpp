#include <QDebug>
#include "rest_controller.h"

RestController::RestController(const ConnectionOptions &connOptions,
							   QObject *parent)
	: QObject(parent), _client(nullptr), _connOptions(connOptions)
{
	qRegisterMetaType<std::vector<DiskInfo> >("std::vector<DiskInfo>");
}

RestController::~RestController()
{
	delete _client;
}

void RestController::init()
{
	_client = new RestClient(_connOptions);
}

void RestController::reqDiskInfo()
{
	Q_ASSERT (_client != nullptr);

	try
	{
		emit diskInfoReceived(_client->getDiskInfo());
	}
	catch (const std::exception &e)
	{
		qCritical() << Q_FUNC_INFO << e.what();
		emit error(e.what());
	}
}
