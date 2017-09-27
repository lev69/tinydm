#ifndef REST_CONTROLLER_H
#define REST_CONTROLLER_H

#include <QObject>
#include <rest_client.h>

class RestController : public QObject
{
	Q_OBJECT
	RestClient *_client;
	ConnectionOptions _connOptions;

public:
	RestController(const ConnectionOptions &connOptions, QObject *parent = 0);
	~RestController();

signals:
	void diskInfoReceived(const std::vector<DiskInfo> &diskList);
	void error(const QString &errMsg);

public slots:
	void init();
	void reqDiskInfo();
};

#endif // REST_CONTROLLER_H
