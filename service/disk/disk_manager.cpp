#include <disk/disk_info_fabric.h>

#ifdef PARTED_FABRIC_DEFINED
#include <disk/parted_disk_info_fabric.h>
#endif

#include "disk_manager.h"

DiskManager::DiskManager()
	: _diskFabric(NULL)
{
#ifdef PARTED_FABRIC_DEFINED
	if (_diskFabric == NULL)
	{
		_diskFabric = new PartedDiskInfoFabric;
	}
#endif
	if (_diskFabric == NULL)
	{
		throw std::runtime_error("No suitable package found to load disk info");
	}
}

vector<DiskInfo> DiskManager::diskList() const
{
	return _diskList;
}

void DiskManager::initDisks()
{
	_diskList = _diskFabric->getDiskInfo();
}
