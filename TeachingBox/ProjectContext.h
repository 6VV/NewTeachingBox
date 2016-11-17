#ifndef _TEACHING_BOX_PROJECT_CONTEXT_H_
#define _TEACHING_BOX_PROJECT_CONTEXT_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ProjectContext.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/09/05
//  Description:	用于记录项目全局变量，包括打开的项目、作用域等信息
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/09/05
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QStringList"

class ProjectContext
{
public:
	static const QString ScopeSystem();
	static const QString ScopeCooperate();
	static const QString ScopeGlobal();
	//static const QString STR_SCOPE_SYSTEM;		/*系统作用域*/
	//static const QString STR_SCOPE_SYNERGIC ;	/*协作作用域*/
	//static const QString STR_SCOPE_GLOBAL;		/*全局作用域*/

	const QStringList SCOPE_ORI;	/*初始作用域*/

public:
	ProjectContext();

	QStringList AllCurrentScopes();

	/*************************************************
	//  Method:        QString CurrentScope()
	//  Description:   获取当前有效的最近作用域，若打开有程序，则选择程序作用域，若打开有项目，则选择项目作用域，否则选择全局作用域
	//  Author:        刘巍 
	//  Date:          2016/11/16
	//  Returns:       QString：当前可选的最近作用域
	//  Parameter:     void
	//  History:       
	*************************************************/
	QString CurrentScope();
	const QStringList& Programs() const;
	QString ProjectLoaded();
	QString ProgramOpened() const;
	void ProgramOpened(const QString& program);
	void ProgramLoading(const QString& program);
	QString ProgramLoading() const;

	void SetLoadedProject(const QString& project, const QStringList& programs);

	bool IsCurrentFileLoad();

	void UnloadProject();

private:
	ProjectContext& operator=(const ProjectContext&);

private:
	QStringList m_currentScopes{};

	QString m_project{};
	QStringList m_programs{};
	QString m_programOpened{};
	QString m_programLoading{};
};

#endif