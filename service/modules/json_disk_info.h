#ifndef DEBUG_DISK_INFO_H
#define DEBUG_DISK_INFO_H

#include <cpprest/json.h>
#include <disk/disk_info.h>

using namespace web;

json::value toJson(const list<DiskInfo> &diskList);
json::value toJson(const DiskInfo &diskInfo);
json::value toJson(const list<PartitionInfo> &parts);
json::value toJson(const PartitionInfo &pi);

#endif // DEBUG_DISK_INFO_H
