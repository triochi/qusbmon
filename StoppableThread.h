/*
 * StoppableThread.h
 *
 *  Created on: Feb 27, 2009
 *      Author: archivator
 */

#ifndef STOPPABLETHREAD_H_
#define STOPPABLETHREAD_H_

#include <QThread>
#include <QReadWriteLock>

class StoppableThread: public QThread
{
public:
	StoppableThread(QObject* parent = 0): QThread(parent){}
	void stop()
	{
		QWriteLocker locker(&stopLock);
		stopping = true;
	}
public slots:
	void start()
	{
		QWriteLocker locker(&stopLock);
		stopping = false;

		QThread::start();
	}
protected:
	QReadWriteLock 	stopLock;
	bool			stopping;
	bool shouldStop()
	{
		QReadLocker locker(&stopLock);
		return stopping;
	}
};


#endif /* STOPPABLETHREAD_H_ */
