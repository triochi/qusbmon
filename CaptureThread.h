/*
 * CaptureThread.h
 *
 *  Created on: Feb 27, 2009
 *      Author: archivator
 */

#ifndef CAPTURETHREAD_H_
#define CAPTURETHREAD_H_

#include <sys/ioctl.h> // ioctl
#include <sys/file.h> // open
#include <string.h> // memcpy

#include <QDebug>
#include <QThread>

#include "StoppableThread.h"
#include "types.h"

#define MON_IOC_MAGIC 0x92

#define MON_IOCQ_URB_LEN _IO(MON_IOC_MAGIC, 1)
#define MON_IOCG_STATS _IOR(MON_IOC_MAGIC, 3, struct mon_bin_stats)
#define MON_IOCT_RING_SIZE _IO(MON_IOC_MAGIC, 4)
#define MON_IOCQ_RING_SIZE _IO(MON_IOC_MAGIC, 5)
#define MON_IOCX_GET   _IOW(MON_IOC_MAGIC, 6, struct mon_bin_get)
#define MON_IOCX_MFETCH _IOWR(MON_IOC_MAGIC, 7, struct mon_bin_mfetch)
#define MON_IOCH_MFLUSH _IO(MON_IOC_MAGIC, 8)

#define BUFFER_SIZE (4096)

class CaptureThread: public StoppableThread
{
	Q_OBJECT
public:
	CaptureThread(QString usbmon = ""): StoppableThread(0), usbmonPath(usbmon) {}
	void setPath(QString path){ usbmonPath = path; }
signals:
	void sendData(mon_bin_get* data);
	void sendStats(unsigned int queued, unsigned int dropped, unsigned int droppedTotal);
protected:
	u32 	droppedCount;
	QString	usbmonPath;
	virtual void run();
};

#endif /* CAPTURETHREAD_H_ */
