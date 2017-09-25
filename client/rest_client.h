#ifndef REST_CLIENT_H
#define REST_CLIENT_H

#include <string>
#include <list>

#include <disk_info.h>

class RestClient
{
public:
	struct Options
	{
		std::string schema;
		std::string host;
		unsigned short port;
		std::string path;
	};

private:
	Options _options;

public:
	RestClient(const Options &options);

	std::list<DiskInfo> getDiskInfo();
};

#endif // REST_CLIENT_H
