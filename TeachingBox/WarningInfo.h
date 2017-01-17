#ifndef _TEACHING_BOX_WARNING_INFO_H_
#define _TEACHING_BOX_WARNING_INFO_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    WarningInfo.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/16
//  Description:    警告信息，包括id、类别、状态、时间、描述
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/16
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QString"
#include "QObject"

class WarningInfo:public QObject
{
public:
	enum Id
	{
		ID_INTERPERTER_ERROR,	/*解释器相关错误*/
		ID_INTERNET_DISCONNECT,	/*断开网络连接*/
		ID_WARNING_TEST,		/*测试警告信息*/
		ID_PRESS_MANUAL_SERVO_BUTTON_AT_AUTO_MODE,	/*在自动模式下按下手动伺服按键*/
		ID_PRESS_AUTO_SERVO_BUTTON_AT_MANUAL_MODE,	/*在手动模式下按下自动伺服按键*/
	};
	enum Category
	{
		CATEGORY_ALL = -1,
		CATEFORY_INFO,	/*信息*/
		CATEFORY_WARNING,	/*警告*/
		CATEFORY_ERROR,	/*错误*/
	};
	enum State
	{
		STATE_SOLVED,	/*已解决*/
		STATE_TO_BE_SOLVED,	/*待解决*/
		STATE_WITHOUT_SOLVE,	/*不需要解决*/
	};

	static const QString DATE_TIME_FORMAT;

public:
	WarningInfo(Id id, const QString& describe = {}, const QDateTime& dateTime = QDateTime::currentDateTime());
	WarningInfo(const WarningInfo& warningInfo);

	QString GetDateTime() const;
	QString GetDescribe() const;
	Category GetCategory() const;
	State GetState() const;

	void SetDateTime(const QString& dateTime);
	void SetState(State state);

private:
	Id m_id; /*信息id*/
	QString m_dateTime;	/*时间*/
	QString m_describe;	/*描述*/
	Category m_category;	/*类别*/
	State m_state;	/*状态*/

private:
	struct WarningMapInfo
	{
		WarningMapInfo(Category category, const QString& describe,State state=WarningInfo::STATE_TO_BE_SOLVED);

		Category category;
		QString describe;
		State state;
	};

	static std::map<Id, WarningMapInfo> s_warningMap;
};

#endif