#ifndef _TEACHING_BOX_REMOTE_MANAGER_H_
#define _TEACHING_BOX_REMOTE_MANAGER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    RemoteManager.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/10/08
//  Description:	远程管理器，用于发送指令给控制器，包括各种运动指令、设置指令等
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/10/08
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QByteArray"
#include "SingleTon.h"
#include <memory>
#include "DataStruct.h"


class RemoteManager
{
	friend SingleTon<RemoteManager>;

public:
	static RemoteManager* GetInstance();

	void SendMovlCommand(const char* commandData,int commandLength,int lineNumber, long long programAddress);
	void SendStopCommand();
	void SendEndCommand();

private:
	RemoteManager();
	~RemoteManager();
	RemoteManager(const RemoteManager&) = delete;
	RemoteManager& operator=(RemoteManager&) = delete;

private:
	void AddLock(char* head,int& offset);		/*添加锁*/
	void AddNormalCommandAttribute(char* head, int& offset, int commandId, int commandLength,int lineNumber,long long programAddress);	/*添加属性*/
	void AddCommand(char* head, int& offset, const char* command,int commandLength);	/*添加命令*/

	QByteArray ContructNormalCommand(int commandId, const char* commandData, int commandLength, int lineNumber, long long programAddress);
	QByteArray ContructNormalCommand(int commandId);
	QByteArray ContructSpecialCommand(int commandId);
};

#endif