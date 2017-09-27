#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets>
#include <QAbstractItemModel>

class MainWindow : public QWidget
{
	Q_OBJECT

	QTreeView *_tableView;

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

signals:
	void needUpdate();

public slots:
	void setModel(QStandardItemModel *model);

private slots:
	void adjustModel();

private:
	void setupUi();
};

#endif // MAIN_WINDOW_H
