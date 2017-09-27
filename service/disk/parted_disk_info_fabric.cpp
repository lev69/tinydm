#include <cassert>

#include "parted_disk_info_fabric.h"

PartedDiskInfoFabric::PartedDiskInfoFabric()
{
}

PartedDiskInfoFabric::~PartedDiskInfoFabric()
{
}

vector<DiskInfo> PartedDiskInfoFabric::getDiskInfo()
{
	return listAllDrives();
}

vector<DiskInfo> PartedDiskInfoFabric::listAllDrives()
{
	vector<DiskInfo> diskList;

	ped_device_probe_all();
	PedDevice *dev = NULL;
	while ((dev = ped_device_get_next(dev)) != NULL)
	{
		DiskInfo diskInfo;

		int64_t sectorSize = dev->sector_size;
		diskInfo.setVolume(dev->path);
		diskInfo.setSize(dev->length * sectorSize);

		diskInfo.setPartitions(listAllPartitions(dev));

		diskList.push_back(diskInfo);
	}
	ped_device_free_all();

	return diskList;
}

vector<PartitionInfo> PartedDiskInfoFabric::listAllPartitions(PedDevice *dev)
{
	PedDisk *disk = ped_disk_new(dev);
	if (disk == NULL)
	{
		cerr << "No disk found on device" << dev->path;
		return vector<PartitionInfo>();
	}

	int partNum = ped_disk_get_last_partition_num(disk);
	PedPartition *part = NULL;

	vector<PartitionInfo> partList;

	for (int i = 1; i <= partNum; ++i)
	{
		part = ped_disk_get_partition(disk, i);
		assert(part != NULL);

		partList.push_back(partitionInfo(part));
	}

	return partList;
}

PartitionInfo PartedDiskInfoFabric::partitionInfo(PedPartition *part)
{
	int64_t sectorSize = part->disk->dev->sector_size;
	PartitionInfo info;
	info.setPartition(ped_partition_get_path(part));
	info.setSize(part->geom.length * sectorSize);
	info.setStart(part->geom.start * sectorSize);

	PedFileSystemType *fsType = ped_file_system_probe(&part->geom);
	if (fsType != NULL)
	{
		info.setFileSystem(fsType->name);
	}
	else
	{
		info.setFileSystem("Unknown");
	}

	return info;
}
