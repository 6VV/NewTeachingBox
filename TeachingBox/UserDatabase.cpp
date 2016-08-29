#include "stdafx.h"
#include "UserDatabase.h"
#include "DatabaseHelper.h"
#include "Exception.h"


namespace Database{

	const QString Database::UserDatabase::GetTextCreateTable()
	{
		QString strUserNameMaxLength = QString::number(TABLE_USER_NAME_MAX_LENGTH);
		QString strUserPasswordMaxLength = QString::number(TABLE_USER_PASSWORD_MAX_LENGTH);

		QString tableText = "CREATE TABLE " + TABLE_USER + " ("
			+ TABLE_COLUMN_NAME + " varchar(" + strUserNameMaxLength + ") NOT NULL,"	/*用户名*/
			+ TABLE_COLUMN_USER_PASSWORD + " varchar(" + strUserPasswordMaxLength + ") NOT NULL,"	/*用户密码*/
			+ TABLE_COLUMN_USER_AUTHORITY + " int NOT NULL,"	/*用户权限*/
			+ TABLE_COLUMN_USER_LANGUAGE + " varchar(" + strUserNameMaxLength + ") NOT NULL)"	/*用户语言*/
			//+ TABLE_COLUMN_USER_IDENTITY + " varchar(" + strUserNameMaxLength + ") NOT NULL)"	/*用户身份*/
			;

		return tableText;
	}

	const QString Database::UserDatabase::TABLE_USER = "UserTable";

	const QString Database::UserDatabase::TABLE_COLUMN_NAME = "name";

	const QString Database::UserDatabase::TABLE_COLUMN_USER_PASSWORD = "password";

	const QString Database::UserDatabase::TABLE_COLUMN_USER_AUTHORITY = "authority";

	const QString Database::UserDatabase::TABLE_COLUMN_USER_LANGUAGE = "language";

	const QString Database::UserDatabase::TABLE_COLUMN_USER_IDENTITY = "indetity";

	void UserDatabase::InsertUserInfo(const User& user)
	{
		QSqlQuery query(DatabaseHelper::GetInstance()->GetDatabase());
		query.prepare("insert into " + TABLE_USER + " values(?,?,?,?)");

		query.bindValue(0, user.GetName());
		query.bindValue(1, user.GetPassword());
		query.bindValue(2, user.GetAuthority());
		query.bindValue(3, user.GetLanguage());

		if (!query.exec())
		{
			throw(Exception("Insert User Table Failed"));
		}
	}

	QList<User> UserDatabase::SelectAllUsers()
	{
		QSqlQuery query(DatabaseHelper::GetInstance()->GetDatabase());
		query.prepare(QString("select * from %1").arg(TABLE_USER));
		QList<User> users;

		if (query.exec())
		{
			while (query.next())
			{
				users.append(User(query.value(0).toString(), query.value(1).toString(), query.value(2).toInt(), query.value(3).toString()));
			}
		}
		else
		{
			throw Exception("Select User Information Failed");
		}

		return users;
	}

	User UserDatabase::SelectUser(const QString& name)
	{
		QSqlQuery query(DatabaseHelper::GetInstance()->GetDatabase());
		query.prepare(QString("select * from %1 where %2='%3'")
			.arg(TABLE_USER)
			.arg(TABLE_COLUMN_NAME)
			.arg(name));

		if (query.exec())
		{
			while (query.next())
			{
				return User(query.value(0).toString(), query.value(1).toString(), query.value(2).toInt(), query.value(3).toString());
			}
		}
		else
		{
			throw Exception("Select User Information Failed");
		}

		return User{};
	}

	void UserDatabase::UpdateUserInfo(const QString& oldUserName, const User& user)
	{
		QSqlQuery query(DatabaseHelper::GetInstance()->GetDatabase());
		query.prepare("update " + TABLE_USER + " set " + TABLE_COLUMN_NAME + "=?,"
			+ TABLE_COLUMN_USER_PASSWORD + "=?,"
			+ TABLE_COLUMN_USER_AUTHORITY + "=?,"
			+ TABLE_COLUMN_USER_LANGUAGE + "=?"
			+ " where " + TABLE_COLUMN_NAME + "=?");

		query.bindValue(0, user.GetName());
		query.bindValue(1, user.GetPassword());
		query.bindValue(2, user.GetAuthority());
		query.bindValue(3, user.GetLanguage());
		query.bindValue(4, oldUserName);

		if (!query.exec())
		{
			throw(Exception("Update User Table Failed"));
		}
	}

	void UserDatabase::DeleteUserInfo(const QString& userName)
	{
		QSqlQuery query(DatabaseHelper::GetInstance()->GetDatabase());
		query.prepare(QString("delete from %1 where %2='%3'").arg(TABLE_USER).arg(TABLE_COLUMN_NAME).arg(userName));

		if (!query.exec())
		{
			throw(Exception("Update User Information Failed"));
		}
	}

}