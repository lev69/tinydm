#include <pplx/pplx.h>
#include <cpprest/http_client.h>
#include <cpprest/uri_builder.h>
#include <cpprest/streams.h>

#include <json_module.h>
#include "rest_client.h"

using namespace std;
using namespace web;
using namespace http;
using namespace client;

using namespace concurrency::streams;

RestClient::RestClient(const ConnectionOptions &options)
	: _options(options)
{
}

std::vector<DiskInfo> RestClient::getDiskInfo()
{
	uri_builder uriBuilder;
	uriBuilder.set_scheme(_options.schema);
	uriBuilder.set_host(_options.host);
	uriBuilder.set_port(_options.port);
	uriBuilder.set_path(_options.path);

	uri_builder partialUri;
	partialUri.append_path(U("/disk/info"));
	auto partialPath = partialUri.to_string();


	http_client client(uriBuilder.to_uri());
	http_response response = client.request(methods::GET, partialPath).get();
	if (response.status_code() != status_codes::OK)
	{
		string errMsg("Server responsed ");
		errMsg += to_string(response.status_code());
		throw runtime_error(errMsg);
	}
	auto bodyStream = response.body();
	stringstreambuf strBuffer;
	bodyStream.read_to_end(strBuffer).wait();
	auto &target = strBuffer.collection();

	auto diskInfoJson = json::value::parse(target);

	return fromJson(diskInfoJson);
}
