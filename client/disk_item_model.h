#ifndef DISK_ITEM_MODEL_H
#define DISK_ITEM_MODEL_H

#include <QAbstractItemModel>

#include <disk_info.h>

class DiskItemModel : public QAbstractItemModel
{
	Q_OBJECT

	vector<DiskInfo> _diskList;

public:
	DiskItemModel(QObject *parent = nullptr);
	~DiskItemModel();

	void initModel(const std::vector<DiskInfo> &diskList);

	// QAbstractItemModel interface
public:
	virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
	virtual QModelIndex parent(const QModelIndex &child) const;
	virtual int rowCount(const QModelIndex &parent) const;
	virtual int columnCount(const QModelIndex &parent) const;
	virtual bool hasChildren(const QModelIndex &parent) const;
	virtual QVariant data(const QModelIndex &index, int role) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // DISK_ITEM_MODEL_H
