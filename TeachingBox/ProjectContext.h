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
private:
	const QString STR_SCOPE_SYSTEM = "SYSTEM";		/*系统作用域*/
	const QString STR_SCOPE_SYNERGIC = "SYNERGIC";	/*协作作用域*/
	const QString STR_SCOPE_GLOBAL = "GLOBAL";		/*全局作用域*/
	const QString STR_SCOPE_PROJECT = "PROJECT";		/*项目作用域*/

	const QStringList SCOPE_ORI;	/*初始作用域*/

public:
	ProjectContext();

	QStringList GetScopes();

private:
	ProjectContext& operator=(const ProjectContext&);

private:
	QStringList m_currentScopes;
};

#endif