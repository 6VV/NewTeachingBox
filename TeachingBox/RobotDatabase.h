#ifndef _TEACHING_BOX_ROBOT_DATABASE_H_
#define _TEACHING_BOX_ROBOT_DATABASE_H_

/*************************************************
//  Copyright (C), 2020-2021, CS&S. Co., Ltd.
//  File name: 	    RobotDatabase.h
//  Author:			刘巍
//  Version: 		1.0
//  Date: 			2021/02/19
//  Description:	机器人数据库管理器，用于添加、删除、修改数据库变量信息等
//  Others:
//  Function List:
//  History:
//    <author>      刘巍
//    <time>        2021/02/19
//    <version>     1.0
//    <desc>        build this moudle
*************************************************/

namespace Database {

	struct RobotStruct {
		QString name;
		int id = -1;
	};

	class RobotDatabase
	{
	private:
		static QString COLUMN_NAME;	//名称列名
		static QString COLUMN_ID;	//ID列名

	public:
		static const QString getTextCreateTable();

		static QString tableName();	//表名
		static void deleteRobot(const QString& name); //删除机器人信息
		static void insertRobot(const QString& name, int id); //插入机器人信息
		static void updateRobot(const QString& oldName, const QString& newName, int id); //更新机器人信息
		static bool existRobotName(const QString& name); //是否存在机器人名
		static bool existRobotId(int id); //是否存在机器人ID

		static QList<RobotStruct> selectRobot(); //查询所有机器人信息
	};

}

#endif