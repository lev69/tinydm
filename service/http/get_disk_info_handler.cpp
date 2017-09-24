#include <disk/disk_manager.h>
#include <modules/json_disk_info.h>

#include "get_disk_info_handler.h"

GetDiskInfoHandler::GetDiskInfoHandler(const http_request &message)
	: AbstractHandler(message)
{
}

GetDiskInfoHandler::~GetDiskInfoHandler()
{
}

void GetDiskInfoHandler::run()
{
	DiskManager *dm = NULL;

	try
	{
		dm = new DiskManager;
		dm->initDisks();
	}
	catch (const std::exception &e)
	{
		cerr << e.what() << endl;
		_message.reply(status_codes::InternalError);
		return;
	}

	auto response = json::value::object();
	response["drives"] = toJson(dm->diskList());
	_message.reply(status_codes::OK, response);
}

