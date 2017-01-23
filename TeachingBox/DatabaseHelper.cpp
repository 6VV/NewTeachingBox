#include "stdafx.h"
#include "DatabaseHelper.h"
#include "UserDatabase.h"
#include "Exception.h"
#include "VariateDatabase.h"

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
		/*是否存在数据库*/
		bool isExists = QFile::exists(DATABASE_NAME);

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

		/*若之前不存在数据库，则创建表*/
		if (!isExists)
		{
			CreateTable();
		}
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
		CreateUserTable();
		CreateVariateTable();
	}

	void DatabaseHelper::CreateUserTable()
	{
		QSqlQuery query(m_db);

		query.prepare(UserDatabase::GetTextCreateTable());

		if (!query.exec())
		{
			throw(Exception("Create User Table Failed"));
		}
	}

	void DatabaseHelper::CreateVariateTable()
	{
		QSqlQuery query(m_db);
	
		query.prepare(VariateDatabase::GetTextCreateTable());

		if (!query.exec())
		{
			throw Exception("Create variate table failed:\n");
		}
	}

}
