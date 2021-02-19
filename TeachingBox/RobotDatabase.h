#ifndef _TEACHING_BOX_ROBOT_DATABASE_H_
#define _TEACHING_BOX_ROBOT_DATABASE_H_

/*************************************************
//  Copyright (C), 2020-2021, CS&S. Co., Ltd.
//  File name: 	    RobotDatabase.h
//  Author:			��Ρ
//  Version: 		1.0
//  Date: 			2021/02/19
//  Description:	���������ݿ��������������ӡ�ɾ�����޸����ݿ������Ϣ��
//  Others:
//  Function List:
//  History:
//    <author>      ��Ρ
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
		static QString COLUMN_NAME;	//��������
		static QString COLUMN_ID;	//ID����

	public:
		static const QString getTextCreateTable();

		static QString tableName();	//����
		static void deleteRobot(const QString& name); //ɾ����������Ϣ
		static void insertRobot(const QString& name, int id); //�����������Ϣ
		static void updateRobot(const QString& oldName, const QString& newName, int id); //���»�������Ϣ
		static bool existRobotName(const QString& name); //�Ƿ���ڻ�������
		static bool existRobotId(int id); //�Ƿ���ڻ�����ID

		static QList<RobotStruct> selectRobot(); //��ѯ���л�������Ϣ
	};

}

#endif