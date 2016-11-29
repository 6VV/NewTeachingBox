#include "stdafx.h"
#include "VariateDatabase.h"
#include "TeachingBoxContext.h"
#include "DatabaseHelper.h"
#include "Exception.h"


namespace Database{

	const QString VariateDatabase::VARIATE_TABLE_NAME{"VariateTable"};
	const QString VariateDatabase::VARIATE_COLUMN_SCOPE{ "scope" };
	const QString VariateDatabase::VARIATE_COLUMN_NAME{ "name" };
	const QString VariateDatabase::VARIATE_COLUMN_VALUE{ "value" };

	void VariateDatabase::InsertVariate(QDataStream& dataStream)
	{
		dataStream.device()->seek(0);
		QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());

		query.prepare("insert into " + VARIATE_TABLE_NAME + " values(?,?,?)");

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
			.arg(VARIATE_TABLE_NAME));

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
		query.prepare("update " + VARIATE_TABLE_NAME + " set "
			+ VARIATE_COLUMN_SCOPE + "=?,"
			+ VARIATE_COLUMN_NAME + "=?,"
			+ VARIATE_COLUMN_VALUE + "=?"
			+ " where "
			+ VARIATE_COLUMN_SCOPE + "=?"
			+ " and "
			+ VARIATE_COLUMN_NAME + "=?");

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

	void VariateDatabase::DeleteVariate(const QString& scope, const QString& name)
	{
		QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());
		QString oper = QString("delete from %1 where %2='%3' and %4='%5'")
			.arg(VARIATE_TABLE_NAME)
			.arg(VARIATE_COLUMN_SCOPE).arg(scope)
			.arg(VARIATE_COLUMN_NAME).arg(name);
		query.prepare(oper);

		if (!query.exec())
		{
			throw Exception("delete variate from database failed:\n" + oper);
		}
	}

	void VariateDatabase::DeleteVariate(const QString& scope)
	{
		QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());
		QString oper = QString("delete from %1 where %2='%3'")
			.arg(VARIATE_TABLE_NAME)
			.arg(VARIATE_COLUMN_SCOPE).arg(scope);
		query.prepare(oper);

		if (!query.exec())
		{
			throw Exception("delete variate from database failed:\n" + oper);
		}
	}

	const QString Database::VariateDatabase::GetTextCreateTable()
	{
		QString length = QString::number(TeachingBoxContext::STRING_MAX_LENGTH);

		QString oper = "CREATE TABLE " + VARIATE_TABLE_NAME + " ("
			+ VARIATE_COLUMN_SCOPE + " varchar("+ length+") NOT NULL,"	/*作用域*/
			+ VARIATE_COLUMN_NAME + " varchar(" + length + ") NOT NULL,"	/*变量名*/
			+ VARIATE_COLUMN_VALUE + " varchar NOT NULL)"	/*值*/;

		return oper;
	}

}