#include <tinydmd_version.h>
#include "get_test_handler.h"

GetTestHandler::GetTestHandler(const http_request &message)
	: AbstractHandler(message)
{
}

GetTestHandler::~GetTestHandler()
{
}

void GetTestHandler::run()
{
	auto response = json::value::object();
	response["version"] = json::value::string(U(tinydmd_version()));
	_message.reply(status_codes::OK, response);
}
