/*
 * DataManager.h
 *
 *  Created on: Feb 28, 2009
 *      Author: archivator
 */

#ifndef DATAMANAGER_H_
#define DATAMANAGER_H_

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>

#include <QDateTime>
#include <QDebug>
#include <QByteArray>
#include <QObject>
#include <QStandardItemModel>
#include <QStringList>

#include "types.h"
#include "SqliteBridge.h"

class DataManager: public QObject{
    Q_OBJECT

protected:
	static 			DataManager* instance;
					DataManager();
	void 			setupDatabase();
	QSqlDatabase	database;
	QStringList		triggeredColumns;
	SQLiteBridge 	bridge;
public:
					~DataManager();
	void			addPacket(const mon_bin_get* packet);
	static 			DataManager& get();
	QStandardItemModel	packets;
public slots:
	void			onRowInserted(QList<QVariant> data);
protected slots:
	void			onProcessPacket(const mon_bin_get* packet);
signals:
	void			processPacket(const mon_bin_get* packet);
};

#endif /* DATAMANAGER_H_ */
