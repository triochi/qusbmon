/*
 * SqliteBridge.h
 *
 *  Created on: Mar 1, 2009
 *      Author: archivator
 */

#ifndef SQLITEBRIDGE_H_
#define SQLITEBRIDGE_H_

#include <QObject>
#include <QString>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlError>
#include <QVariant>
#include <QByteArray>
#include <sqlite3.h>

/* SQLiteBridge
 *
 * This class handles insert triggers, given a database and table.
 * It is a workaround for the fact that the QtSql module does not
 * update its models on a change - I don't know why this is the
 * case (they could handle all the stuff at the Qt level, without triggers)
 * but it's a fact.
 *
 * The static function serves as a trigger handler and its 1st parameter is
 * the trigger type (currently, only 'insert' is supported)
 */
class SQLiteBridge: public QObject
{
    Q_OBJECT
public:
					SQLiteBridge(){}
					SQLiteBridge(QSqlDatabase& db){ setDatabase(db); }
	void 			setDatabase(QSqlDatabase& db);
	void 			addInsertTrigger(const QString& tableName, const QStringList& columns);
protected:
	sqlite3*		handle;
	QSqlDatabase 	database;

	static void 	scalarHandler(sqlite3_context* context, int, sqlite3_value** values);

	inline void 	emitRowInserted(QList<QVariant> rowData)
	{
		emit rowInserted(rowData);
	}
signals:
	void 			rowInserted(QList<QVariant> rowData);
};

#endif /* SQLITEBRIDGE_H_ */
