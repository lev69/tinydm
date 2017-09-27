#include <algorithm>

#include "disk_info.h"

void DiskInfo::setVolume(const string &volume)
{
	_volume = volume;
}

int64_t DiskInfo::size() const
{
	return _size;
}

void DiskInfo::setSize(int64_t size)
{
	_size = size;
}

DiskInfo::DiskInfo()
{
}

void DiskInfo::setPartitions(const vector<PartitionInfo> &partList)
{
	_partitions = partList;
}

void DiskInfo::addPartition(const PartitionInfo &part)
{
	_partitions.push_back(part);
}

vector<PartitionInfo> DiskInfo::partitions() const
{
	return _partitions;
}

string DiskInfo::volume() const
{
	return _volume;
}

class Print
{
	ostream &_s;
public:
	Print(ostream &s) : _s(s) {}
	void operator()(const PartitionInfo &pi) { _s << pi << endl; }
};

ostream &operator <<(ostream &stream, const DiskInfo &info)
{
	stream << "device: " << info.volume() << endl;
	stream << "size: " << info.size() << endl;
	stream << "partitions" << endl;
	auto partList = info.partitions();
	for_each (partList.begin(), partList.end(), Print(stream));
	return stream;
}
