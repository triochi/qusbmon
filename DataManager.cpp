#include "DataManager.h"
#include <QMessageBox>

DataManager* DataManager::instance = 0;

DataManager::DataManager()
{
	triggeredColumns << "id" << "urb_id" << "bus" << "device" << "endpoint" << "time" << "status";
	packets.setColumnCount(triggeredColumns.size());

	QStringList headers;
	headers << "#" << "URB #" << "Bus" << "Device" << "Endpoint" << "Time" << "Status";
	packets.setHorizontalHeaderLabels(headers);

	setupDatabase();

	QObject::connect(&bridge, SIGNAL(rowInserted(QList<QVariant>)), this, SLOT(onRowInserted(QList<QVariant>)), Qt::DirectConnection);
	QObject::connect(this, SIGNAL(processPacket(const mon_bin_get*)), this, SLOT(onProcessPacket(const mon_bin_get*)), Qt::QueuedConnection);
}

DataManager::~DataManager()
{
	database.close();
}

void DataManager::setupDatabase()
{
    QSqlDatabase::database("in_mem_db", false).close();
    QSqlDatabase::removeDatabase("in_mem_db");

	database = QSqlDatabase::addDatabase("QSQLITE");
	database.setHostName("");
	database.setDatabaseName(":memory:");
    if (!database.open())
       qDebug() <<"Unable to open database" << "An error occurred while "<<
                                                "opening the connection: "<< database.lastError().text();
	database.transaction();
	QSqlQuery packetsTable = database.exec("CREATE TABLE `packets` ("
			"id INTEGER PRIMARY KEY,"
			"urb_id INTEGER,"
			"bus INTEGER,"
			"device INTEGER,"
			"endpoint INTEGER,"
			"time TEXT,"
			"status TEXT,"
			"raw BLOB);");

	QSqlQuery dataTable = database.exec("CREATE TABLE `data` ("
				"id INTEGER PRIMARY KEY,"
				"packet_id INTEGER,"
				"type STRING," /*"Setup", "Data"*/
				"data BLOB);");
	database.commit();
	if (database.lastError().type() != QSqlError::NoError)
			qDebug() << database.lastError().databaseText();

	bridge.setDatabase(database);
	bridge.addInsertTrigger("packets", triggeredColumns);
}

DataManager& DataManager::get()
{
	if (DataManager::instance == 0)
		DataManager::instance = new DataManager();

	return *(DataManager::instance);
}

void DataManager::addPacket(const mon_bin_get* packet)
{
	emit processPacket(packet);
}
void DataManager::onProcessPacket(const mon_bin_get* packet)
{
	QSqlQuery packetQuery;
	packetQuery.prepare("INSERT INTO `packets` "
			"(urb_id, device, bus, endpoint, time, status) "
			"VALUES(?,?,?,?,?,?);");
	QSqlQuery dataQuery;
	dataQuery.prepare("INSERT INTO `data` "
				"(packet_id, data, type) "
				"VALUES(?, ?, ?);");
	packetQuery.bindValue(0, packet->header->id);
	packetQuery.bindValue(1, packet->header->device);
	packetQuery.bindValue(2, packet->header->bus);
	packetQuery.bindValue(3, packet->header->endpoint);
	packetQuery.bindValue(4, QDateTime::fromTime_t(packet->header->ts_sec).addMSecs(packet->header->ts_usec/1000).toString("hh:mm:ss.zzz"));
	packetQuery.bindValue(5, (unsigned char)packet->header->status);

	if(!packetQuery.exec())
		goto error;

	dataQuery.bindValue(0, packetQuery.lastInsertId().toUInt());
	packetQuery.finish();

	if(packet->header->flag_setup == 0)
	{
		QByteArray setupData((const char*) packet->header->setup, 8);
		dataQuery.bindValue(1, setupData);
		dataQuery.bindValue(2, "Setup");
	}
	else if(packet->header->lengthCaptured > 0)
	{
		QByteArray data((const char*) packet->data, packet->header->lengthCaptured);
		dataQuery.bindValue(1, data);
		dataQuery.bindValue(2, "Data");
	}

	if(dataQuery.boundValues().size() == 3 && !dataQuery.exec())
		goto error;

	dataQuery.finish();
	goto cleanup;

error:
	database.rollback();
	qDebug() << "Database error: " << database.lastError().databaseText() << database.lastError().driverText();
	goto cleanup;

cleanup:
	delete packet->header;
	delete[] (char*)packet->data;
	delete packet;
	return;
}

void DataManager::onRowInserted(QList<QVariant> data)
{
	QList <QStandardItem*> columns;
	for(int i=0; i<data.size(); ++i)
	{
		QStandardItem* column = new QStandardItem;
		column->setData(data[i], Qt::DisplayRole);
		columns.append(column);
	}
	packets.appendRow(columns);
}
