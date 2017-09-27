#include <settings_dialog.h>
#include <main_window.h>
#include <rest_controller.h>

#include "controller.h"

enum Column : int
{
	Name,
	Begin,
	End,
	Size,
	FS,

	Count // total column count
};

Controller::Controller(QObject *parent)
	: QObject(parent)
{
	_diskModel = new QStandardItemModel(this);
	_diskModel->setHorizontalHeaderLabels(QStringList()
										  << tr("Device")
										  << tr("Begin")
										  << tr("End")
										  << tr("Size")
										  << tr("File System"));
}

Controller::~Controller()
{
	_restThread.quit();
	_restThread.wait();
}

void Controller::init()
{
	SettingsDialog sd;
	if (sd.exec() == QDialog::Rejected)
	{
		qDebug() << "Rejected";
		qApp->quit();
		return;
	}

	ConnectionOptions connOptions = sd.connectionOptions();
	qDebug() << "Accepted: " << connOptions.schema.data() << "://"
			 << connOptions.host.data() << ":" << connOptions.port
			 << "/" << connOptions.path.data();

	RestController *restCtl = new RestController(connOptions);
	restCtl->moveToThread(&_restThread);
	connect(&_restThread, &QThread::started,
			restCtl, &RestController::init);
	connect(&_restThread, &QThread::finished,
			restCtl, &RestController::deleteLater);
	connect(restCtl, &RestController::diskInfoReceived,
			this, &Controller::updateDiskInfo);
	_restThread.start();
	QTimer::singleShot(0, restCtl, &RestController::reqDiskInfo);

	MainWindow *w = new MainWindow;
	connect(w, &MainWindow::needUpdate,
			restCtl, &RestController::reqDiskInfo);
	w->setModel(_diskModel);
	w->showMaximized();
}

void Controller::updateDiskInfo(const std::vector<DiskInfo> &diskList)
{
	QStandardItem *root = _diskModel->invisibleRootItem();
	_diskModel->removeRows(0, root->rowCount(), root->index());
	for_each (diskList.begin(), diskList.end(), [=](const DiskInfo &disk)
	{
		QStandardItem *diskPartItem = new QStandardItem(disk.volume().data());
		QStandardItem *diskBeginItem = new QStandardItem(QString::number(0));
		QStandardItem *diskEndItem = new QStandardItem(QString::number(disk.size()));
		QStandardItem *diskSizeItem = new QStandardItem(QString::number(disk.size()));
		QStandardItem *diskFSItem = new QStandardItem(tr("Unsupported"));

		QList<QStandardItem*> diskItems;
				diskItems << diskPartItem << diskBeginItem << diskEndItem << diskSizeItem << diskFSItem;
		auto partList = disk.partitions();
		for_each (partList.begin(), partList.end(), [=](const PartitionInfo &part)
		{
			auto begin = part.start();
			auto size = part.size();
			auto end = begin + size;
			QStandardItem *partItem = new QStandardItem(part.partition().data());
			QStandardItem *partBeginItem = new QStandardItem(QString::number(begin));
			QStandardItem *partEndItem = new QStandardItem(QString::number(end));
			QStandardItem *partSizeItem = new QStandardItem(QString::number(size));
			QStandardItem *partFSItem = new QStandardItem(part.fileSystem().data());
			QList<QStandardItem*> partItems;
			partItems << partItem << partBeginItem << partEndItem << partSizeItem << partFSItem;

			diskPartItem->appendRow(partItems);
		});

		root->appendRow(diskItems);
	});
}
