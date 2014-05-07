/*
 * main.h
 *
 *  Created on: Feb 27, 2009
 *      Author: archivator
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <QApplication>
#include <QDebug>
#include <QMetaType>

#include "DataManager.h"
#include "MainWindow.h"
#include "DeviceSelect.h"
#include "CaptureThread.h"

class Application: public QApplication
{
	Q_OBJECT
public:
	Application(int argc, char** argv);
public slots:
	void		toggleCapture(bool);
	void		receiveData(mon_bin_get* data);
	void		receiveStats(unsigned int queued, unsigned int dropped, unsigned int droppedTotal);
	void 		quit();
protected:
	void 		setupSignals();
	MainWindow 	mainWindow;
	QString		usbmonPath;
	CaptureThread captureThread;
};

#endif /* MAIN_H_ */
