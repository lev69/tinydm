#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <disk_info.h>
#include <disk_item_model.h>

class Controller : public QObject
{
	Q_OBJECT

	QThread _restThread;
	DiskItemModel _diskModel;

public:
	Controller(QObject *parent = 0);
	~Controller();

signals:
	void modelUpdated(QAbstractItemModel *model);

public slots:
	void init();
	void updateDiskInfo(const std::list<DiskInfo> &diskList);
};

#endif // CONTROLLER_H
