#include <disk_item_model.h>
#include <settings_dialog.h>
#include <main_window.h>
#include <rest_controller.h>

#include "controller.h"

Controller::Controller(QObject *parent)
	: QObject(parent)
{
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
	w->setModel(_diskModel.model());
//	connect(this, &Controller::modelUpdated,
//			w, &MainWindow::setModel);
	w->show();
}

void Controller::updateDiskInfo(const std::list<DiskInfo> &diskList)
{
	qDebug() << Q_FUNC_INFO;
	_diskModel.initModel(diskList);
//	emit modelUpdated(_diskModel.model());
}
