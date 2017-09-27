#include <stdint.h>

#include "settings_dialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi();
}

SettingsDialog::~SettingsDialog()
{
}

ConnectionOptions SettingsDialog::connectionOptions() const
{
	ConnectionOptions options;
	options.schema = _schemaComboBox->currentText().toStdString();
	options.host = _hostAddressEdit->text().toStdString();
	options.port = _portSpinBox->value();
	options.path = _pathLineEdit->text().toStdString();

	return options;
}

void SettingsDialog::setupUi()
{
	QLabel *schemaLabel = new QLabel(tr("Schema"));
	_schemaComboBox = new QComboBox;
	QStringList schemas = QStringList() << "http" << "https";
	_schemaComboBox->addItems(schemas);
	_schemaComboBox->setEditable(false);
	_schemaComboBox->setCurrentIndex(0);

	QLabel *hostAddressLabel = new QLabel(tr("Host address"));
	_hostAddressEdit = new QLineEdit("127.0.0.1");

	QLabel *portLabel = new QLabel(tr("Port"));
	_portSpinBox = new QSpinBox;
	_portSpinBox->setMinimum(1);
	_portSpinBox->setMaximum(USHRT_MAX);
	_portSpinBox->setValue(80);

	QLabel *pathLabel = new QLabel(tr("API path"));
	_pathLineEdit = new QLineEdit("api");

	QDialogButtonBox *dialogButtonBox = new QDialogButtonBox;
	dialogButtonBox->addButton(tr("Close"), QDialogButtonBox::RejectRole);
	dialogButtonBox->addButton(tr("Connect"), QDialogButtonBox::AcceptRole);
	connect(dialogButtonBox, &QDialogButtonBox::accepted,
			this, &SettingsDialog::accept);
	connect(dialogButtonBox, &QDialogButtonBox::rejected,
			this, &SettingsDialog::reject);

	QGridLayout *mainLayout = new QGridLayout;

	Qt::Alignment leftColAlignment = Qt::AlignLeft | Qt::AlignVCenter;
	Qt::Alignment rightColAlignment = Qt::AlignLeft | Qt::AlignVCenter;
	mainLayout->addWidget(schemaLabel, 0, 0, leftColAlignment);
	mainLayout->addWidget(_schemaComboBox, 0, 1, rightColAlignment);
	mainLayout->addWidget(hostAddressLabel, 1, 0, leftColAlignment);
	mainLayout->addWidget(_hostAddressEdit, 1, 1, rightColAlignment);
	mainLayout->addWidget(portLabel, 2, 0, leftColAlignment);
	mainLayout->addWidget(_portSpinBox, 2, 1, rightColAlignment);
	mainLayout->addWidget(pathLabel, 3, 0, leftColAlignment);
	mainLayout->addWidget(_pathLineEdit, 3, 1, rightColAlignment);
	mainLayout->addWidget(dialogButtonBox, 4, 0, 1, 2, Qt::AlignRight);

	setLayout(mainLayout);
}
