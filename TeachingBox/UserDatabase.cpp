#include "stdafx.h"
#include "UserDatabase.h"
#include "DatabaseHelper.h"
#include "Exception.h"


namespace Database{

	const QString Database::UserDatabase::GetTextCreateTable()
	{
		QString strUserNameMaxLength = QString::number(TableNameMaxLength());
		QString strUserPasswordMaxLength = QString::number(TablePasswordMaxLength());

		QString tableText = "CREATE TABLE " + TableUser() + " ("
			+ TableColumnName() + " varchar(" + strUserNameMaxLength + ") NOT NULL,"	/*用户名*/
			+ TableColumnPassword() + " varchar(" + strUserPasswordMaxLength + ") NOT NULL,"	/*用户密码*/
			+ TableColumnAuthority() + " int NOT NULL,"	/*用户权限*/
			+ TableColumnLanguage() + " varchar(" + strUserNameMaxLength + ") NOT NULL)"	/*用户语言*/
			//+ TABLE_COLUMN_USER_IDENTITY + " varchar(" + strUserNameMaxLength + ") NOT NULL)"	/*用户身份*/
			;

		return tableText;
	}


	void UserDatabase::InsertUserInfo(const User& user)
	{
		QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());
		query.prepare("insert into " + TableUser() + " values(?,?,?,?)");

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
		QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());
		query.prepare(QString("select * from %1").arg(TableUser()));
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
		QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());
		query.prepare(QString("select * from %1 where %2='%3'")
			.arg(TableUser())
			.arg(TableColumnName())
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
		QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());
		query.prepare("update " + TableUser() + " set " + TableColumnName() + "=?,"
			+ TableColumnPassword() + "=?,"
			+ TableColumnAuthority() + "=?,"
			+ TableColumnLanguage() + "=?"
			+ " where " + TableColumnName() + "=?");

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
		QSqlQuery query(*DatabaseHelper::GetInstance()->GetDatabase());
		query.prepare(QString("delete from %1 where %2='%3'").arg(TableUser()).arg(TableColumnName()).arg(userName));

		if (!query.exec())
		{
			throw(Exception("Update User Information Failed"));
		}
	}


	int UserDatabase::TableNameMaxLength()
	{
		return TeachingBoxContext::STRING_MAX_LENGTH;
	}

	int UserDatabase::TablePasswordMaxLength()
	{
		return TeachingBoxContext::STRING_MAX_LENGTH;
	}

	QString UserDatabase::TableUser()
	{
		return "UserTable";
	}

	QString UserDatabase::TableColumnName()
	{
		return "name";
	}

	QString UserDatabase::TableColumnPassword()
	{
		return "password";
	}

	QString UserDatabase::TableColumnAuthority()
	{
		return "authority";
	}

	QString UserDatabase::TableColumnLanguage()
	{
		return "language";
	}

	QString UserDatabase::TableColumnIdentity()
	{
		return "indetity";
	}

}