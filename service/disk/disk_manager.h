#ifndef DISK_MANAGER_H
#define DISK_MANAGER_H

#include <disk/disk_info_fabric.h>

class DiskManager
{
	DiskInfoFabric *_diskFabric;
	vector<DiskInfo> _diskList;

public:
	DiskManager();

	vector<DiskInfo> diskList() const;

	void initDisks();
};

#endif // DISK_MANAGER_H
