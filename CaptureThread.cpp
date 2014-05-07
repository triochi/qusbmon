#include "CaptureThread.h"

void CaptureThread::run()
{
	mon_bin_hdr header;
	mon_bin_get data;
	mon_bin_stats stats;
	char buffer[BUFFER_SIZE];

    int fd = open(usbmonPath.toStdString().data(), O_RDONLY);

	if(fd < 0)
	{
		qDebug() << "Could not open " << usbmonPath;
		return;
	}

	unsigned char statsCounter = 0;
	droppedCount = 0;

	while(true)
	{
		statsCounter += 1;
		memset(&header, 0, sizeof(mon_bin_hdr));
		memset(&data, 0, sizeof(mon_bin_get));
		memset(buffer, 0, BUFFER_SIZE);

		if (shouldStop())
			return;

		if (statsCounter % 20 == 0)
		{
			statsCounter = 0;
			memset(&stats, 0, sizeof(mon_bin_stats));
			ioctl(fd, MON_IOCG_STATS, &stats);

			droppedCount += stats.dropped;

			emit sendStats(stats.queued, stats.dropped, droppedCount);
		}
		data.header = &header;
		data.data = buffer;
		data.length = BUFFER_SIZE;

		ioctl(fd, MON_IOCX_GET, &data);

		if (shouldStop())
			return;

		mon_bin_get* event = new mon_bin_get;
		mon_bin_hdr* eventHeader = new mon_bin_hdr;

		memcpy(eventHeader, &header, sizeof(mon_bin_hdr));
		memcpy(event, &data, sizeof(mon_bin_get));

		event->header = eventHeader;

		char * eventData;
		if(event->header->lengthCaptured != 0)
		{
			eventData = new char[event->header->lengthCaptured];
			memcpy(eventData, data.data, event->header->lengthCaptured);
		}
		else
			eventData = 0;

		event->data = eventData;

		emit sendData(event);

		if(shouldStop())
			return;

	}
}
