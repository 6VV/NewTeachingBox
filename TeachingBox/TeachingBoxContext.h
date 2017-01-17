#ifndef _TEACHING_BOX_TEACHING_BOX_CONTEXT_H_
#define _TEACHING_BOX_TEACHING_BOX_CONTEXT_H_

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

class TeachingBoxContext
{
public:
	static const int STRING_MAX_LENGTH = 128;

public:
	static TeachingBoxContext* GetInstance();

private:
	TeachingBoxContext();
	TeachingBoxContext(const TeachingBoxContext&) = delete;
	TeachingBoxContext& operator=(const TeachingBoxContext&) = delete;
	~TeachingBoxContext() = default;

public:
	QString GetLanguage();
	User GetUser();
	QRect GetScreenRect();

	bool IsMotOn();
	bool IsServoOn();

	void SetIsMotOn(bool isMotOn);
	void SetTeachingBoxRect(const QRect& rect);
	void SetScreenRect(const QRect& rect);
	void SetIsServoOn(bool isServoOn);
	void SetLanguage(const QString& language);
	void SetUser(const User& user);

private:
	User m_user{};
	QString m_language;
	QPoint m_screenPos{};
	QPoint m_teachingBoxPos{};
	QSize m_screenSize{};
	QRect m_teachingBoxRect{};
	QRect m_screenRect{};

	bool m_isServoOn = false;
	bool m_isMotOn = false;
};


#endif