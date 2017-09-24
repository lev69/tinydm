#include <string>
#include <iostream>
#include <functional>

#include <cpprest/http_listener.h>
#include <cpprest/http_msg.h>
#include <cpprest/uri_builder.h>

#include <http/get_test_handler.h>
#include <http/get_disk_info_handler.h>

#include "rest_service.h"

using namespace std;
using namespace web;
using namespace http;
using namespace experimental::listener;

RestService::RestService(const Options &options)
	: _options(options), _httpService(NULL)
{
}

void RestService::handleGet(http_request message)
{
	auto path = requestPath(message);
	if (!path.empty())
	{
		AbstractHandler *handler = NULL;
		if (path[0] == "test")
		{
			handler = new GetTestHandler(message);
		}
		else if (path[0] == "disk")
		{
			if ((path.size() > 1) && (path[1] == "info"))
			{
				handler = new GetDiskInfoHandler(message);
			}
		}

		if (handler != NULL)
		{
			handler->run();
			delete handler;
			return;
		}
	}

	message.reply(status_codes::BadRequest);
}

void RestService::init()
{
	uri_builder uriBuilder;
	uriBuilder.set_scheme(U("http"));
	uriBuilder.set_host(U("0.0.0.0"));
	uriBuilder.set_port(_options.servicePort);
	uriBuilder.set_path(U("api"));

	_httpService = new http_listener(uriBuilder.to_uri());
	_httpService->support(methods::GET, std::bind(&RestService::handleGet, this,
												  std::placeholders::_1));
	_httpService->open().wait();
	cout << "service started at " << uriBuilder.to_string() << endl;
}

std::vector<utility::string_t>
RestService::requestPath(const http_request & message)
{
	auto relativePath = uri::decode(message.relative_uri().path());
	return uri::split_path(relativePath);
}
