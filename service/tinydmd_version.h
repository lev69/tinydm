#ifndef TINYDMD_VERSION_H
#define TINYDMD_VERSION_H

#include <service_cmake_config.h>

#define STR(a) #a
#define VERSION_STR(x,y,z) STR(x) "." STR(y) "." STR(z)

inline const char *tinydmd_version()
{
	return VERSION_STR(tinydmd_VERSION_MAJOR,
					   tinydmd_VERSION_MINOR,
					   tinydmd_VERSION_PATCH);
}

#endif // TINYDMD_VERSION_H
