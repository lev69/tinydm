#ifndef TEST_REST_HANDLER_H
#define TEST_REST_HANDLER_H

#include <http/abstract_handler.h>

class GetTestHandler : public AbstractHandler
{
public:
	GetTestHandler(const http_request &message);
	virtual ~GetTestHandler();

	void run() override;
};

#endif // TEST_REST_HANDLER_H
