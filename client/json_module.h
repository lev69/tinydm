#ifndef JSON_MODULE_H
#define JSON_MODULE_H

#include <vector>
#include <cpprest/json.h>
#include <disk_info.h>

using namespace web;

std::vector<DiskInfo> fromJson(const json::value &diskInfoJson);
DiskInfo diskFromJson(const json::value &diskJson);
std::vector<PartitionInfo> partListFromJson(const json::value &partListJson);
PartitionInfo partFromJson(const json::value &partJson);

#endif // JSON_MODULE_H
