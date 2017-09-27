#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets>
#include <QAbstractItemModel>

class MainWindow : public QWidget
{
	Q_OBJECT

	QTableView *_tableView;

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

signals:

public slots:
	void setModel(QAbstractItemModel *model);

private:
	void setupUi();
};

#endif // MAIN_WINDOW_H
