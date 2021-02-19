#ifndef _TEACHING_BOX_DATABASE_H_
#define _TEACHING_BOX_DATABASE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    Database.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/08/29
//  Description:	用于获取或创建数据库，
//					若数据库不存在，则创建数据库，并创建所需表
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/08/29
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "SingleTon.h"

namespace Database{

	class DatabaseHelper
	{
		friend SingleTon<DatabaseHelper>;

	public:
		static DatabaseHelper* GetInstance();
		const QSqlDatabase* GetDatabase();

	private:
		DatabaseHelper();
		DatabaseHelper(const DatabaseHelper&);
		DatabaseHelper& operator=(const DatabaseHelper&);
		~DatabaseHelper();

		void CreateTable();	/*创建所有表*/
		void Exec(const QString& text); //执行数据库语句

	private:
		const QString DATABASE_TYPE = "QSQLITE";	/*数据库类型*/
		const QString HOST_NAME = "localhost";		/*数据库主机名*/
		const QString DATABASE_NAME = "teaching_box.db"; /*数据库名*/
		const QString USER_NAME = "Administrator";	/*用户名*/
		const QString PASSWORD = "123456";			/*密码*/

		const QString CONNECTION_NAME = "teachingbox";	/*连接名*/
		QSqlDatabase m_db;	/*数据库*/
	};

}
#endif