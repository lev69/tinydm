#ifndef DISK_MANAGER_H
#define DISK_MANAGER_H

#include <disk/disk_info_fabric.h>

class DiskManager
{
	DiskInfoFabric *_diskFabric;
	list<DiskInfo> _diskList;

public:
	DiskManager();

	list<DiskInfo> diskList() const;

	void initDisks();
};

#endif // DISK_MANAGER_H
