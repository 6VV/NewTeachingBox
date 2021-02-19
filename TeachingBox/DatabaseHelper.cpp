#include "stdafx.h"
#include "DatabaseHelper.h"
#include "UserDatabase.h"
#include "Exception.h"
#include "VariateDatabase.h"
#include "QSqlError"
#include "RobotDatabase.h"

namespace Database{

	DatabaseHelper* DatabaseHelper::GetInstance()
	{
		return SingleTon<DatabaseHelper>::GetInstance();
	}

	const QSqlDatabase* DatabaseHelper::GetDatabase()
	{
		return &m_db;
	}

	DatabaseHelper::DatabaseHelper()
	{
		if (m_db.contains(CONNECTION_NAME))
		{
			m_db = QSqlDatabase::database(CONNECTION_NAME);
		}
		else
		{
			m_db = QSqlDatabase::addDatabase(DATABASE_TYPE, CONNECTION_NAME);
			m_db.setHostName(HOST_NAME);
			m_db.setDatabaseName(DATABASE_NAME);
			m_db.setUserName(USER_NAME);
			m_db.setPassword(PASSWORD);
		}
		if (!m_db.isOpen())
		{
			m_db.open();
		}

		CreateTable(); //若表不存在，创建表
	}

	DatabaseHelper::~DatabaseHelper()
	{
		if (m_db.isOpen())
		{
			m_db.close();
		}
	}

	void DatabaseHelper::CreateTable()
	{
		Exec(UserDatabase::GetTextCreateTable()); //创建用户表
		Exec(VariateDatabase::GetTextCreateTable()); //创建变量表
		Exec(RobotDatabase::getTextCreateTable()); //创建机器人表

	}

	void DatabaseHelper::Exec(const QString& text)
	{
		QSqlQuery query(m_db);
		query.prepare(text);

		if (!query.exec())
		{
			qDebug() << query.lastError().text();
			throw Exception(query.lastError().text());
		}
	}

}
