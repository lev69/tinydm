#include <iostream>

#include <tinydmd_version.h>
#include <service_cmake_config.h>
#include <http/rest_service.h>
#include <modules/interrupt_handler.h>

using namespace std;

int main(int, char **)
{
	InterruptHandler::hookSIGINT();

	cout << "app version: " << tinydmd_version() << endl;

	RestService::Options options;
	options.servicePort = 80;
	RestService service(options);
	service.init();

	InterruptHandler::waitForUserInterrupt();

	return 0;
}
