#ifndef DEVICE_SELECT_H
#define DEVICE_SELECT_H

#include <QDialog>
#include <QList>
#include <QDirModel>
#include "ui_deviceselect.h"

class DeviceSelectDialog : public QDialog, private Ui::deviceSelectClass
{
    Q_OBJECT

public:
	DeviceSelectDialog(QWidget *parent = 0);
    ~DeviceSelectDialog();
    QString getPath(){ return path; }
protected:
	QString path;
	void setupTree();
	QDirModel* usbmonModel;
public slots:
	void accept();
protected slots:
	void selectedPath(const QModelIndex& index);
};

#endif // DEVICE_SELECT_H
