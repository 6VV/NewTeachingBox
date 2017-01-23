#ifndef _TEACHING_BOX_VARIATE_DATABASE_H_
#define _TEACHING_BOX_VARIATE_DATABASE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    VariateDatabase.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/09/02
//  Description:	变量数据库管理器，用于添加、删除、修改数据库变量信息等
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/09/02
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/
#include "QVector"

class QDataStream;
class QByteArray;

namespace Database{

	class VariateDatabase
	{
	private:
		static QString TableName();	/*表名*/
		static QString ColumnScope();	/*作用域列名*/
		static QString ColumnName();	/*变量名列名*/
		static QString ColumnValue();	/*值列名*/

	public:
		static const QString GetTextCreateTable();

		static void DeleteScope(const QString& scope, const QString& name);
		static void DeleteScope(const QString& scope);
		static void InsertVariate(QDataStream& dataStream);
		static QVector<QByteArray> SelectAllVariates();
		static void UpdateVariate(const QString& scope, const QString& name, QDataStream& dataStream);
	};

}

#endif