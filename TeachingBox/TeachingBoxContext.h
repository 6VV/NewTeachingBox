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

class TVariate;

class TeachingBoxContext
{
public:
	static const int STRING_MAX_LENGTH = 128;

	enum JogState
	{
		AXIS,
		XYZ,
	};

public:
	static TeachingBoxContext* GetInstance();

private:
	TeachingBoxContext();
	TeachingBoxContext(const TeachingBoxContext&) = delete;
	TeachingBoxContext& operator=(const TeachingBoxContext&) = delete;
	~TeachingBoxContext() = default;

public:
	std::shared_ptr<TVariate> GetCurrentRefSys();
	std::shared_ptr<TVariate> GetCurrentToolSys();
	JogState GetJogState();
	QString GetLanguage();
	User GetUser();
	QRect GetScreenRect();

	bool IsMotOn();
	bool IsServoOn();

	void SetCurrentRefSys(std::shared_ptr<TVariate> refSys);
	void SetCurrentToolSys(std::shared_ptr<TVariate> toolSys);
	void SetIsMotOn(bool isMotOn);
	void SetJog(JogState jogState);
	void SetTeachingBoxRect(const QRect& rect);
	void SetScreenRect(const QRect& rect);
	void SetIsServoOn(bool isServoOn);
	void SetLanguage(const QString& language);
	void SetUser(const User& user);

private:
	std::shared_ptr<TVariate> m_currentRefSys;
	std::shared_ptr<TVariate> m_currentToolSys;

	bool m_isServoOn = false;
	bool m_isMotOn = false;

	JogState m_jogState = JogState::AXIS;
	QString m_language;
	QPoint m_screenPos{};
	QSize m_screenSize{};
	QRect m_screenRect{};
	QPoint m_teachingBoxPos{};
	QRect m_teachingBoxRect{};
	User m_user{};


};


#endif