#ifndef _TEACHING_BOX_CONTEXT_H_
#define _TEACHING_BOX_CONTEXT_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TeachingBoxContext.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/07/28
//  Description:	用于记录当前示教盒的一些全局状态
//  Others:			
//  History:
//    <author>      刘巍 
//    <time>        2016/07/28
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "User.h"
#include "QPoint"
#include "QSize"

namespace TeachingBoxContext
{
	const int STRING_MAX_LENGTH = 128;

	enum ExecuteMode
	{
		AUTO,
		STEP,
		MANUAL,
	};

	QString GetLanguage();
	User GetUser();

	QRect GetScreenRect();

	void SetTeachingBoxRect(const QRect& rect);
	void SetScreenRect(const QRect& rect);

	void SetExecuteMode(ExecuteMode mode);
	void SetLanguage(const QString& language);
	void SetUser(const User& user);
}


#endif