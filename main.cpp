#include "main.h"
#include <bits/predefs.h>


int main(int argc, char *argv[])
{
    Application app(argc, argv);
    return app.exec();
}

Application::Application(int argc, char** argv): QApplication(argc, argv)
{
	mainWindow.show();
	setupSignals();
}

void Application::setupSignals()
{
	QObject::connect(&mainWindow, SIGNAL(toggleCapture(bool)), this, SLOT(toggleCapture(bool)));
	QObject::connect(&captureThread, SIGNAL(sendStats(unsigned int, unsigned int, unsigned int)), this, SLOT(receiveStats(unsigned int, unsigned int, unsigned int)), Qt::QueuedConnection);
	QObject::connect(&captureThread, SIGNAL(sendData(mon_bin_get*)), this, SLOT(receiveData(mon_bin_get*)), Qt::DirectConnection);
}
void Application::toggleCapture(bool toggle)
{
	if(toggle)
	{
		DeviceSelectDialog dialog(&mainWindow);
		if(dialog.exec() == QDialog::Accepted)
		{
			usbmonPath = dialog.getPath();

			captureThread.setPath(usbmonPath);
			qDebug() << "Starting capture thread on " << usbmonPath;
			captureThread.start();
		}
		else
			mainWindow.setCapturing(false);
	}
	else
	{
		captureThread.stop();
		qDebug() << "Stopping capture thread";
	}
}

void Application::receiveData(mon_bin_get* data)
{
	DataManager::get().addPacket(data);
}
void Application::receiveStats(unsigned int queued, unsigned int dropped, unsigned int droppedTotal)
{
	QString status("Packets: %1(Q) %2(D)");
	status = status.arg(queued).arg(droppedTotal);

	(void) dropped; // TODO: Mark dropped packages using blank rows

	mainWindow.setStatus(status);
}

void Application::quit()
{
	captureThread.stop();
	captureThread.wait();

	QApplication::quit();
}
