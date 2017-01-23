#include "stdafx.h"
#include "VariateDatabase.h"
#include "TeachingBoxContext.h"
#include "DatabaseHelper.h"
#include "Exception.h"
#include "TimeCalculator.h"


namespace Database{

	QString VariateDatabase::TableName()
	{
		return "VariateTable";
	}

	QString VariateDatabase::ColumnScope()
	{
		return "scope";
	}

	QString VariateDatabase::ColumnName()
	{
		return "name";
	}

	QString VariateDatabase::ColumnValue()
	{
		return "value";
	}

	void VariateDatabase::InsertVariate(QDataStream& dataStream)
	{
		dataStream.device()->seek(0);
		QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());

		query.prepare("insert into " + TableName() + " values(?,?,?)");

		QString scope;
		QString name;
		QByteArray value;

		dataStream >> scope;
		dataStream >> name;
		dataStream.device()->seek(0);
		value = dataStream.device()->readAll();

		query.bindValue(0, scope);
		query.bindValue(1, name);
		query.bindValue(2, value);

		if (!query.exec())
		{
			throw Exception("insert into database failed");
		}

	}

	QVector<QByteArray> VariateDatabase::SelectAllVariates()
	{
		QVector<QByteArray> result;

		QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());

		query.prepare(QString("select * from %1")
			.arg(TableName()));

		if (!query.exec())
		{
			throw Exception("select variates from database failed");
		}

		while (query.next())
		{
			result.append(query.value(2).toByteArray());
		}

		return std::move(result);
	}

	void VariateDatabase::UpdateVariate(const QString& scope, const QString& name, QDataStream& dataStream)
	{
		QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());
		query.prepare("update " + TableName() + " set "
			+ ColumnScope() + "=?,"
			+ ColumnName() + "=?,"
			+ ColumnValue() + "=?"
			+ " where "
			+ ColumnScope() + "=?"
			+ " and "
			+ ColumnName() + "=?");

		dataStream.device()->seek(0);
		QString newScope;
		QString newName;
		QByteArray newValue;

		dataStream >> newScope;
		dataStream >> newName;
		dataStream.device()->seek(0);
		newValue = dataStream.device()->readAll();

		query.bindValue(0, newScope);
		query.bindValue(1, newName);
		query.bindValue(2, newValue);
		query.bindValue(3, scope);
		query.bindValue(4, name);

		if (!query.exec())
		{
			throw Exception("update variate in database failed");
		}
	}

	void VariateDatabase::DeleteScope(const QString& scope, const QString& name)
	{
		QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());
		QString oper = QString("delete from %1 where %2='%3' and %4='%5'")
			.arg(TableName())
			.arg(ColumnScope()).arg(scope)
			.arg(ColumnName()).arg(name);
		query.prepare(oper);

		if (!query.exec())
		{
			throw Exception("delete variate from database failed:\n" + oper);
		}
	}

	void VariateDatabase::DeleteScope(const QString& scope)
	{
		QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());
		QString oper = QString("delete from %1 where %2='%3'")
			.arg(TableName())
			.arg(ColumnScope()).arg(scope);
		query.prepare(oper);

		if (!query.exec())
		{
			throw Exception("delete variate from database failed:\n" + oper);
		}
	}

	const QString Database::VariateDatabase::GetTextCreateTable()
	{
		QString length = QString::number(TeachingBoxContext::STRING_MAX_LENGTH);

		QString oper = "CREATE TABLE " + TableName() + " ("
			+ ColumnScope() + " varchar(" + length + ") NOT NULL,"	/*作用域*/
			+ ColumnName() + " varchar(" + length + ") NOT NULL,"	/*变量名*/
			+ ColumnValue() + " varchar NOT NULL)"	/*值*/;

		return oper;
	}

}