#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <QtWidgets>
#include <connection_options.h>

class SettingsDialog : public QDialog
{
	Q_OBJECT

	QComboBox *_schemaComboBox;
	QLineEdit *_hostAddressEdit;
	QSpinBox *_portSpinBox;
	QLineEdit *_pathLineEdit;

public:
	SettingsDialog(QWidget *parent = 0);
	~SettingsDialog();

	ConnectionOptions connectionOptions() const;

private:
	void setupUi();
};

#endif // SETTINGS_DIALOG_H
