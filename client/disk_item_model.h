#ifndef DISK_ITEM_MODEL_H
#define DISK_ITEM_MODEL_H

#include <QStandardItemModel>

#include <disk_info.h>

class DiskItemModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	DiskItemModel(QObject *parent = nullptr);
	~DiskItemModel();

	void initModel(const std::list<DiskInfo> &diskList);
	QStandardItemModel *model() const;
};

#endif // DISK_ITEM_MODEL_H
