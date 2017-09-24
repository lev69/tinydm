#include "abstract_handler.h"

AbstractHandler::AbstractHandler(const http_request &message)
	: _message(message)
{
}

AbstractHandler::~AbstractHandler()
{
}
