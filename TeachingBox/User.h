#ifndef _TEACHING_BOX_USER_H_
#define _TEACHING_BOX_USER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    User.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/08/01
//  Description:	用户信息，包括用户名、用户密码、用户权限、语言、身份
//  Others:
//  History:
//    <author>      刘巍 
//    <time>        2016/08/01
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include<QString>

class User
{
public:
	User();
	User(const QString& name, const QString& password, int authority, const QString& language);

	QString GetName() const;
	QString GetPassword() const;
	int GetAuthority() const;
	QString GetLanguage() const;

private:
	QString m_name;
	QString m_password;
	int m_authority;
	QString m_language;
};

#endif