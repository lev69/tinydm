#include <disk_info.h>

#include "disk_item_model.h"

enum Column : int
{
	Name,
	Begin,
	End,
	Size,
	FS,

	Count // total column count
};

DiskItemModel::DiskItemModel(QObject *parent)
	: QAbstractItemModel(parent)
{
}

DiskItemModel::~DiskItemModel()
{
}

void DiskItemModel::initModel(const std::vector<DiskInfo> &diskList)
{
	beginResetModel();
	_diskList = diskList;
	endResetModel();
}

QModelIndex
DiskItemModel::index(int row, int column, const QModelIndex &parent) const
{
	if (parent.isValid())
	{
		if (parent.parent().isValid())
		{
			return QModelIndex();
		}
		const DiskInfo &disk = _diskList.at(parent.row());
		if ((row < (int)disk.partitions().size()) && (column < Column::Count))
		{
			return createIndex(row, column);
		}
	}
	else
	{
		if ((row < (int)_diskList.size()) && (column < Column::Count))
		{
			return createIndex(row, column);
		}
	}

	return QModelIndex();
}

QModelIndex
DiskItemModel::parent(const QModelIndex &child) const
{

}

int
DiskItemModel::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
	{
		if (parent.parent().isValid())
		{
			return 0;
		}
		else
		{
			return _diskList.at(parent.row()).partitions().size();
		}
	}
	else
	{
		return _diskList.size();
	}
}

int
DiskItemModel::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
	{
		return Column::Count;
	}

	return 0;
}

bool DiskItemModel::hasChildren(const QModelIndex &parent) const
{
	/* Only top-level items can have children
	 */
	if (parent.parent().isValid())
	{
		return false;
	}
	else if (parent.column() == 0)
	{
		return !_diskList.at(parent.row()).partitions().empty();
	}
	else
	{
		return false;
	}
}

QVariant DiskItemModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	if (role == Qt::DisplayRole)
	{
		if (index.parent().isValid())
		{
			//leaves
			int diskId = index.parent().row();
			int partId = index.row();
			const DiskInfo &disk = _diskList[diskId];
			const PartitionInfo &part = disk.partitions().at(partId);
			switch (index.column())
			{
			case Column::Name:
				return part.partition().data();
			case Column::Begin:
				return static_cast<qint64>(part.start());
			case Column::End:
				return static_cast<qint64>(part.start()) +
						static_cast<qint64>(part.size());
			case Column::Size:
				return static_cast<qint64>(part.size());
			case Column::FS:
				return part.fileSystem().data();
			}
		}
		else
		{
			// roots
			int diskId = index.row();
			const DiskInfo &disk = _diskList[diskId];
			switch (index.column())
			{
			case Column::Name:
				return disk.volume().data();
			case Column::Begin:
				return 0;
			case Column::End:
				return static_cast<qint64>(disk.size());
			case Column::Size:
				return static_cast<qint64>(disk.size());
			case Column::FS:
				return tr("Unsupported");
			}
		}
	}

	return QVariant();
}

QVariant DiskItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if ((orientation == Qt::Vertical) && (role == Qt::DisplayRole))
	{
		switch (section)
		{
		case Column::Name:
			return tr("Device");
		case Column::Begin:
			return tr("Begin");
		case Column::End:
			return tr("End");
		case Column::Size:
			return tr("Size");
		case Column::FS:
			return tr("File System");
		default:
			return QVariant();
		}
	}
	return QVariant();
}
