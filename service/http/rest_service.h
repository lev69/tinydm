#ifndef REST_SERVICE_H
#define REST_SERVICE_H

#include <cpprest/http_msg.h>
#include <cpprest/http_listener.h>

using namespace web;
using namespace http;
using namespace experimental::listener;

class RestService
{
public:
	struct Options
	{
		short servicePort;
	};

private:
	Options _options;
	http_listener *_httpService;

public:
	RestService(const Options &options);

	void init();
	void handleGet(http_request message);

private:
	json::object responseNotImpl(const http::method & method);
	std::vector<utility::string_t> requestPath(const http_request & message);
};

#endif // REST_SERVICE_H
