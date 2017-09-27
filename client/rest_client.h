#ifndef REST_CLIENT_H
#define REST_CLIENT_H

#include <string>
#include <list>

#include <disk_info.h>
#include <connection_options.h>

class RestClient
{
private:
	ConnectionOptions _options;

public:
	RestClient(const ConnectionOptions &options);

	std::list<DiskInfo> getDiskInfo();
};

#endif // REST_CLIENT_H
