#ifndef _TEACHIGN_BOX_USER_DATABASE_H_
#define _TEACHIGN_BOX_USER_DATABASE_H_

#include "TeachingBoxContext.h"

namespace Database{

	class UserDatabase
	{
	public:
		static const QString GetTextCreateTable();

		/*用户表相关*/
		static void InsertUserInfo(const User& user);	/*插入新用户*/
		static QList<User> SelectAllUsers();	/*获取所有用户*/
		static User SelectUser(const QString& name);
		static void UpdateUserInfo(const QString& oldUserName, const User& user);	/*更新用户信息*/
		static void DeleteUserInfo(const QString& userName);	/*删除用户信息*/

	private:
		static int TableNameMaxLength();	/*用户名最大长度*/
		static int TablePasswordMaxLength();	/*用户密码最大长度*/
		static QString TableUser();	/*用户表名*/
		static QString TableColumnName();	/*用户名列名*/
		static QString TableColumnPassword();	/*用户密码列名*/
		static QString TableColumnAuthority();	/*用户权限列名*/
		static QString TableColumnLanguage();	/*用户语言*/
		static QString TableColumnIdentity();	/*用户身份*/

	};

}

#endif