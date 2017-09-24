#ifndef ABSTRACT_HANDLER_H
#define ABSTRACT_HANDLER_H

#include <cpprest/http_msg.h>

using namespace web;
using namespace http;

class AbstractHandler
{
protected:
	http_request _message;
	AbstractHandler(const http_request &message);

public:
	virtual ~AbstractHandler();
	virtual void run() = 0;
};

#endif // ABSTRACT_HANDLER_H
