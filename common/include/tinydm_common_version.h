#ifndef TINYDM_COMMON_VERSION_H
#define TINYDM_COMMON_VERSION_H

#include <common_cmake_config.h>

#define STR(a) #a
#define VERSION_STR(x,y,z) STR(x) "." STR(y) "." STR(z)

inline const char *tinydm_common_version()
{
	return VERSION_STR(tinydm_common_VERSION_MAJOR,
					   tinydm_common_VERSION_MINOR,
					   tinydm_common_VERSION_PATCH);
}

#endif // TINYDM_COMMON_VERSION_H
