#ifndef DISK_INFO_FABRIC_H
#define DISK_INFO_FABRIC_H

#include <disk_info.h>

class DiskInfoFabric
{
public:
	DiskInfoFabric();
	virtual ~DiskInfoFabric();

	virtual vector<DiskInfo> getDiskInfo() = 0;
};

#endif // DISK_INFO_FABRIC_H
