#ifndef _TEACHING_BOX_BROADCAST_H_
#define _TEACHING_BOX_BROADCAST_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    Broadcast.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/12
//  Description:    示教盒广播，提供部分信号，用于示教盒内信号的传递、控制
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/12
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QObject"
#include "TeachingBoxContext.h"

class WarningInfo;

class TeachingBoxBroadcast :public QObject
{
	Q_OBJECT

public:
	static TeachingBoxBroadcast* GetInstance()
	{
		static TeachingBoxBroadcast broadcast;
		return &broadcast;
	}

private:
	TeachingBoxBroadcast()=default;
	TeachingBoxBroadcast(const TeachingBoxBroadcast&) = delete;
	TeachingBoxBroadcast& operator =(const TeachingBoxBroadcast&) = delete;
	~TeachingBoxBroadcast() = default;

signals:
	void ExecuteModeChanged(int newMode);
	void ExecuteStateChanged(int newState);
	void JogStateChanged(TeachingBoxContext::JogState state);
	void ServoStateChanged(bool isOn);
	void LoadProject(const QString& project, const QStringList& programs);
	void LoadFilesChanged();	/*已加载的文件数发生变化*/
	void OpenProgram(const QString& project, const QString& program);
	void WarningThrowed(const WarningInfo& warningInfo);
	void WarningStateChanged();
};

#endif