#ifndef _TEACHING_BOX_PROJECT_MANAGER_H_
#define _TEACHING_BOX_PROJECT_MANAGER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    FileManager.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/09/05
//  Description:	文件管理器，用于管理机器人项目文件，包括查询、添加、删除等功能
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/09/05
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QMap"

class QTreeWidgetItem;

class ProjectManager
{
private:
	static const QString PROJECT_PATH;
	static const QString FILE_SUFFIX ;

public:
	bool CreateProject(const QString& project);
	bool CreateProgram(const QString& project, const QString& program);

	void DeleteProject(const QString& name);
	void DeleteProgram(const QString& project,const QString& program);

	void GetAllFiles(QTreeWidgetItem* parent);
	QStringList GetProjectFiles(const QString& project);
	QStringList GetStateTexts(const QString& fileName);

	bool ExistProject(const QString& project);
	bool ExistProgram(const QString& project, const QString& program);

private:
	void GetAllFilesFromPath(const QString & path, QTreeWidgetItem* parent);
	QString GetWholeFileName(const QString& fileName);
};

#endif