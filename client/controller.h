#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QStandardItemModel>
#include <disk_info.h>

class Controller : public QObject
{
	Q_OBJECT

	QThread _restThread;
	QStandardItemModel *_diskModel;

public:
	Controller(QObject *parent = 0);
	~Controller();

signals:
	void modelUpdated(QAbstractItemModel *model);

public slots:
	void init();
	void updateDiskInfo(const std::vector<DiskInfo> &diskList);
	void onError(const QString &msg);
};

#endif // CONTROLLER_H
