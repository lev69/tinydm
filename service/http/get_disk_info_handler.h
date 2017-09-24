#ifndef DISK_REST_HANDLER_H
#define DISK_REST_HANDLER_H

#include <http/abstract_handler.h>

class GetDiskInfoHandler : public AbstractHandler
{
public:
	GetDiskInfoHandler(const http_request &message);
	virtual ~GetDiskInfoHandler();

	void run() override;
};

#endif // DISK_REST_HANDLER_H
