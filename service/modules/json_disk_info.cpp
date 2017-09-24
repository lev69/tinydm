#include "json_disk_info.h"

json::value toJson(const list<DiskInfo> &diskList)
{
	auto diskArray = json::value::array();
	int idx = 0;
	for (auto i = diskList.begin(); i != diskList.end(); ++i)
	{
		diskArray[idx++] = toJson(*i);
	}
	auto result = json::value::object();
	result["drives"] = diskArray;

	return result;
}

json::value toJson(const DiskInfo &diskInfo)
{
	auto json = json::value::object();
	json["device"] = json::value::string(diskInfo.volume());
	json["size"] = diskInfo.size();
	json["partitions"] = toJson(diskInfo.partitions());

	return json;
}

json::value toJson(const list<PartitionInfo> &parts)
{
	auto json = json::value::array();
	int idx = 0;
	for (auto i = parts.begin(); i != parts.end(); ++i)
	{
		json[idx++] = toJson(*i);
	}

	return json;
}

json::value toJson(const PartitionInfo &pi)
{
	auto json = json::value::object();
	json["partition"] = json::value::string(pi.partition());
	json["start"] = pi.start();
	json["size"] = pi.size();
	json["file_system"] = json::value::string(pi.fileSystem());

	return json;
}
