#include "stdafx.h"
#include "RobotDatabase.h"
#include "TeachingBoxContext.h"
#include "DatabaseHelper.h"
#include "QSqlError"

QString Database::RobotDatabase::COLUMN_NAME = "name";
QString Database::RobotDatabase::COLUMN_ID = "id";

const QString Database::RobotDatabase::getTextCreateTable()
{
	QString length = QString::number(TeachingBoxContext::STRING_MAX_LENGTH);

	QString oper = "CREATE TABLE IF NOT EXISTS " + tableName() + " ("
		+ COLUMN_NAME + " varchar(" + length + ") NOT NULL,"	//Ãû³Æ
		+ COLUMN_ID + " int NOT NULL)";	//ID

	return oper;
}

QString Database::RobotDatabase::tableName()
{
	return "robot";
}

void Database::RobotDatabase::deleteRobot(const QString& name)
{
	QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());
	QString oper = QString("delete from %1 where %2='%3'")
		.arg(tableName())
		.arg(COLUMN_NAME)
		.arg(name);

	query.prepare(oper);
	if (!query.exec())
	{
		qDebug() << query.lastError().text();
	}
}

void Database::RobotDatabase::insertRobot(const QString& name, int id)
{
	QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());

	query.prepare(QString("insert into %1(%2,%3) values(?,?)").arg(tableName()).arg(COLUMN_NAME).arg(COLUMN_ID));

	query.bindValue(0, name);
	query.bindValue(1, id);

	if (!query.exec())
	{
		qDebug() << query.lastError().text();
	}
}

void Database::RobotDatabase::updateRobot(const QString& oldName, const QString& newName, int id)
{
	QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());
	query.prepare(QString("update %1 set %2=?,%3=? where %2=?")
		.arg(tableName())
		.arg(COLUMN_NAME)
		.arg(COLUMN_ID));

	query.bindValue(0, newName);
	query.bindValue(1, id);
	query.bindValue(2, oldName);

	if (!query.exec())
	{
		qDebug() << query.lastError().text();
	}
}

bool Database::RobotDatabase::existRobotName(const QString& name)
{
	QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());
	query.prepare(QString("select count(*) from %1 where %2='%3'")
		.arg(tableName())
		.arg(COLUMN_NAME)
		.arg(name));

	if (!query.exec())
	{
		qDebug() << query.lastError().text();
		return false;
	}

	int count = 0;
	while (query.next())
	{
		count = query.value(0).toInt();
	}
	return count > 0;
}

bool Database::RobotDatabase::existRobotId(int id)
{
	QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());
	query.prepare(QString("select count(*) from %1 where %2='%3'")
		.arg(tableName())
		.arg(COLUMN_ID)
		.arg(QString::number(id)));

	if (!query.exec())
	{
		qDebug() << query.lastError().text();
		return false;
	}

	int count = 0;
	while (query.next())
	{
		count = query.value(0).toInt();
	}
	return count > 0;
}

QList<Database::RobotStruct> Database::RobotDatabase::selectRobot()
{
	QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());
	query.prepare(QString("select %1,%2 from %3")
		.arg(COLUMN_NAME)
		.arg(COLUMN_ID)
		.arg(tableName()));

	if (!query.exec())
	{
		qDebug() << query.lastError().text();
		return {};
	}

	QList<RobotStruct> robots;
	while (query.next())
	{
		RobotStruct robot;
		robot.name = query.value(0).toString();
		robot.id = query.value(1).toInt();
		robots.append(robot);
	}

	return robots;
}
