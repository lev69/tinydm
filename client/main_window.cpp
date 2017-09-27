#include "main_window.h"

#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	setupUi();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setModel(QStandardItemModel *model)
{
	_tableView->setModel(model);
	connect(model, &QStandardItemModel::rowsInserted,
			this, &MainWindow::adjustModel);
}

void MainWindow::adjustModel()
{
	_tableView->expandAll();
	_tableView->resizeColumnToContents(0);
	_tableView->setVisible(true);
}

void MainWindow::setupUi()
{
	_tableView = new QTreeView;
	_tableView->setVisible(false);
	_tableView->setSelectionMode(QAbstractItemView::NoSelection);
	_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QPushButton *updateButton = new QPushButton(tr("Update"));
	connect(updateButton, &QPushButton::clicked,
			this, &MainWindow::needUpdate);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(_tableView, 1);
	mainLayout->addWidget(updateButton, 0, Qt::AlignRight);
	setLayout(mainLayout);
}
