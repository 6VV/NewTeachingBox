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
		static const int TABLE_USER_NAME_MAX_LENGTH = TeachingBoxContext::STRING_MAX_LENGTH;	/*用户名最大长度*/
		static const int TABLE_USER_PASSWORD_MAX_LENGTH = TeachingBoxContext::STRING_MAX_LENGTH;	/*用户密码最大长度*/

		static const QString TABLE_USER;	/*用户表名*/
		static const QString TABLE_COLUMN_NAME;	/*用户名列名*/
		static const QString TABLE_COLUMN_USER_PASSWORD;	/*用户密码列名*/
		static const QString TABLE_COLUMN_USER_AUTHORITY;	/*用户权限列名*/
		static const QString TABLE_COLUMN_USER_LANGUAGE;	/*用户语言*/
		static const QString TABLE_COLUMN_USER_IDENTITY;	/*用户身份*/
	};

}

#endif