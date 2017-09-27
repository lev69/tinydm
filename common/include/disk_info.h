#ifndef DISK_INFO_H
#define DISK_INFO_H

#include <iostream>
#include <vector>
#include <string>

#include <partition_info.h>

using namespace std;

class DiskInfo
{
	vector<PartitionInfo> _partitions;
	string _volume;
	int64_t _size;

public:
	DiskInfo();

	void setPartitions(const vector<PartitionInfo> &partList);
	void addPartition(const PartitionInfo &part);
	vector<PartitionInfo> partitions() const;

	string volume() const;
	void setVolume(const string &volume);

	int64_t size() const;
	void setSize(int64_t size);
};

ostream &operator <<(ostream &stream, const DiskInfo &info);

#endif // DISK_INFO_H
