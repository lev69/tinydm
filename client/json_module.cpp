#include <string>

#include <tinydm_common_version.h>
#include "json_module.h"

using namespace std;

vector<DiskInfo> fromJson(const json::value &diskInfoJson)
{
	string serverLibVersion = diskInfoJson.at("lib_version").as_string();
	string myVersion = tinydm_common_version();
	if (myVersion != serverLibVersion)
	{
		string errMsg =
				string("Library versions are different.\nLocal version: ") +
				myVersion +  "\nServer version: " + serverLibVersion;
		throw runtime_error(errMsg);
	}

	auto drives = diskInfoJson.at("drives").as_array();
	vector<DiskInfo> diskList;

	for_each (drives.begin(), drives.end(), [&diskList](json::value value)
	{
		diskList.push_back(diskFromJson(value));
	});

	return diskList;
}

DiskInfo diskFromJson(const json::value &diskJson)
{
	DiskInfo info;
	info.setVolume(diskJson.at("device").as_string());
	info.setSize(diskJson.at("size").as_number().to_int64());
	info.setPartitions(partListFromJson(diskJson.at("partitions")));

	return info;
}

std::vector<PartitionInfo> partListFromJson(const json::value &partListJson)
{
	auto parts = partListJson.as_array();
	vector<PartitionInfo> partList;
	for_each (parts.begin(), parts.end(), [&partList](json::value value)
	{
		partList.push_back(partFromJson(value));
	});

	return partList;
}

PartitionInfo partFromJson(const json::value &partJson)
{
	PartitionInfo info;
	info.setPartition(partJson.at("partition").as_string());
	info.setFileSystem(partJson.at("file_system").as_string());
	info.setSize(partJson.at("size").as_number().to_int64());
	info.setStart(partJson.at("start").as_number().to_int64());

	return info;
}
