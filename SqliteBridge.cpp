#include "SqliteBridge.h"

void SQLiteBridge::setDatabase(QSqlDatabase& db)
{
	database = db;
	QVariant v = database.driver()->handle();
	if (v.isValid() && qstrcmp(v.typeName(), "sqlite3*")==0) {
		sqlite3 *handle = *static_cast<sqlite3 **>(v.data());
		if (handle != 0)
		{
			this->handle = (sqlite3*) handle;
            if(sqlite3_create_function(this->handle,
                                       "bridgescalar",
                                       -1,
                                       SQLITE_UTF8,
                                       this,
                                       &SQLiteBridge::scalarHandler,
                                       NULL,
                                       NULL) != SQLITE_OK)
				qDebug() << "Could not create scalar function";
		}
		else
			qDebug() << "Could not get sqlite handle";
	}
	else
		qDebug() << "Could not get proper QVariant for sqlite handle";
}
void SQLiteBridge::scalarHandler(sqlite3_context* context, int args, sqlite3_value** values)
{
	QString type;
	if(sqlite3_value_type(values[0]) != SQLITE_TEXT)
		return;
	else
		type = (const char*) sqlite3_value_text(values[0]);

	QList<QVariant> returnValues;

	for (int i=1; i < args; i++)
	{
		sqlite3_value* value = values[i];
		QVariant data;
		switch(sqlite3_value_type(value))
		{
		case SQLITE_INTEGER: data = QVariant::fromValue<int>(sqlite3_value_int(value)); break;
		case SQLITE_TEXT: data = QVariant::fromValue<QString>(QString((const char*)sqlite3_value_text(value))); break;
		case SQLITE_FLOAT: data = QVariant::fromValue<double>(sqlite3_value_double(value)); break;
		case SQLITE_BLOB:
			{
				const char* raw = (const char* ) sqlite3_value_blob(value);
				QByteArray array(raw, sqlite3_value_bytes(value));
				data = QVariant::fromValue<QByteArray>(array);
			}
		}
		returnValues.append(data);
	}
	SQLiteBridge* ptr = (SQLiteBridge* )sqlite3_user_data(context);

	if (type == "insert")
		ptr->emitRowInserted(returnValues);
	else
		qDebug() << "Unknown trigger type";
}

void SQLiteBridge::addInsertTrigger(const QString& tableName, const QStringList& columns)
{
	if (columns.size() < 1)
		return;

	QStringList newColumns(columns);
	for(int i=0; i<newColumns.size(); ++i)
		newColumns[i] = newColumns[i].prepend("NEW.");


	QString query("CREATE TRIGGER insert_trigger_%1 AFTER INSERT ON `%1` FOR EACH ROW BEGIN \
					SELECT bridgescalar('insert', %2); \
					END;");
	query = query.arg(tableName).arg(newColumns.join(", "));

	if (database.exec(query).lastError().type() != QSqlError::NoError)
		qDebug() << "Could not add trigger: " << database.lastError().databaseText() << database.lastError().driverText() << "\n" << query;
	else
		qDebug() << "Added INSERT trigger on " << tableName;
}
