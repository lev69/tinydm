#include "partition_info.h"

string PartitionInfo::fileSystem() const
{
	return _fileSystem;
}

void PartitionInfo::setFileSystem(const string &fileSystem)
{
	_fileSystem = fileSystem;
}

string PartitionInfo::label() const
{
	return _label;
}

void PartitionInfo::setLabel(const string &label)
{
	_label = label;
}

int64_t PartitionInfo::start() const
{
	return _start;
}

void PartitionInfo::setStart(int64_t start)
{
	_start = start;
}

int64_t PartitionInfo::size() const
{
	return _size;
}

void PartitionInfo::setSize(int64_t size)
{
	_size = size;
}

PartitionInfo::PartitionInfo()
{
}

string PartitionInfo::partition() const
{
	return _partition;
}

void PartitionInfo::setPartition(const string &partition)
{
	_partition = partition;
}

ostream &operator <<(ostream &stream, const PartitionInfo &info)
{
	stream << "partition: " << info.partition() << endl;
	stream << "start: " << info.start() << " byte" << endl;
	stream << "size: " << info.size() << " bytes" << endl;
	stream << "file system: " << info.fileSystem() << endl;

	return stream;
}
