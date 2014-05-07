#include "DeviceSelect.h"

DeviceSelectDialog::DeviceSelectDialog(QWidget *parent)
    : QDialog(parent)
{
	setupUi(this);
	setupTree();
}

void DeviceSelectDialog::setupTree()
{
	QStringList usbmonDevices;
	usbmonModel = new QDirModel(QStringList("usbmon*"), QDir::System, QDir::Name);

	devicesView->setAllColumnsShowFocus(true);
	devicesView->setModel(usbmonModel);
	devicesView->hideColumn(1);
	devicesView->hideColumn(2);
	devicesView->hideColumn(3);
	devicesView->hideColumn(4);
	devicesView->hideColumn(5);
	devicesView->setRootIndex(usbmonModel->index("/dev"));

	QObject::connect(devicesView, SIGNAL(activated(const QModelIndex&)), this, SLOT(selectedPath(const QModelIndex&)));
}

void DeviceSelectDialog::accept()
{
	selectedPath(devicesView->selectionModel()->currentIndex());

	QDialog::accept();
}

void DeviceSelectDialog::selectedPath(const QModelIndex& index)
{
	if(!index.isValid() || index.data().value<QString>().size() == 0)
		reject();

	path = QString("/dev/") + index.data().value<QString>();

	QDialog::accept();
}

DeviceSelectDialog::~DeviceSelectDialog()
{

}
