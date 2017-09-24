#ifndef PARTED_DISK_INFO_FABRIC_H
#define PARTED_DISK_INFO_FABRIC_H

extern "C"
{
#include <parted/device.h>
#include <parted/disk.h>
#include <parted/filesys.h>
}

#include <disk/disk_info_fabric.h>

class PartedDiskInfoFabric : public DiskInfoFabric
{
public:
	PartedDiskInfoFabric();
	virtual ~PartedDiskInfoFabric();

	virtual list<DiskInfo> getDiskInfo();

private:
	list<DiskInfo> listAllDrives();
	list<PartitionInfo> listAllPartitions(PedDevice *dev);
	PartitionInfo partitionInfo(PedPartition *part);
};

#endif // PARTED_DISK_INFO_FABRIC_H
