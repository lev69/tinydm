#include <disk_info.h>

#include "disk_item_model.h"

enum DataRole
{
	SizeRole = Qt::UserRole + 1,
	BeginRole,
	FSRole
};

DiskItemModel::DiskItemModel(QObject *parent)
	: QObject(parent)
{
	_model = new QStandardItemModel;
}

DiskItemModel::~DiskItemModel()
{
	delete _model;
}

void DiskItemModel::initModel(const std::list<DiskInfo> &diskList)
{
	Q_ASSERT (_model != NULL);
	QStandardItem *root = _model->invisibleRootItem();
	_model->removeRows(0, _model->rowCount(root->index()), root->index());

	std::for_each (diskList.begin(), diskList.end(), [=](const DiskInfo &disk)
	{
		QStandardItem *diskItem = new QStandardItem;
		diskItem->setText(disk.volume().data());
		diskItem->setData(static_cast<qint64>(disk.size()), SizeRole);

		auto partList = disk.partitions();
		std::for_each (partList.begin(), partList.end(), [=](const PartitionInfo &part)
		{
			QStandardItem *partItem = new QStandardItem;
			partItem->setText(part.partition().data());
			partItem->setData(static_cast<qint64>(part.size()), SizeRole);
			partItem->setData(static_cast<qint64>(part.start()), BeginRole);
			partItem->setData(part.fileSystem().data(), FSRole);

			diskItem->appendRow(partItem);
		});
		root->appendRow(diskItem);
	});
}

QStandardItemModel *DiskItemModel::model() const
{
	return _model;
}
