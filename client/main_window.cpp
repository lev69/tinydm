#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	setupUi();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setModel(QAbstractItemModel *model)
{
	_tableView->setModel(model);
}

void MainWindow::setupUi()
{
	_tableView = new QTableView;
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(_tableView);
	setLayout(mainLayout);
}
