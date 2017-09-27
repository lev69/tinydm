#ifndef CONNECTION_OPTIONS_H
#define CONNECTION_OPTIONS_H

#include <string>

struct ConnectionOptions
{
	std::string schema;
	std::string host;
	unsigned short port;
	std::string path;
};

#endif // CONNECTION_OPTIONS_H
