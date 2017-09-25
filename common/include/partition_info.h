#ifndef PARTITION_INFO_H
#define PARTITION_INFO_H

#include <iostream>
#include <string>

using namespace std;

class PartitionInfo
{
	string _partition;
	string _fileSystem;
	string _label;
	int64_t _start;
	int64_t _size;

public:
	PartitionInfo();

	string partition() const;
	void setPartition(const string &partition);

	string fileSystem() const;
	void setFileSystem(const string &fileSystem);

	string label() const;
	void setLabel(const string &label);

	int64_t start() const;
	void setStart(int64_t start);

	int64_t size() const;
	void setSize(int64_t size);
};

ostream &operator <<(ostream &stream, const PartitionInfo &info);

#endif // PARTITION_INFO_H
