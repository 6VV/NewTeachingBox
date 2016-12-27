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

class DataStream;

class RemoteManager
{
	friend SingleTon<RemoteManager>;

public:
	static RemoteManager* GetInstance();

	void SendCommand(const DataStream& stream);
	void SendStopCommand();
	void SendEndCommand();
	void SendCommandToGetPosition();
	void SendCommandToGetPose();

private:
	RemoteManager();
	~RemoteManager();
	RemoteManager(const RemoteManager&) = delete;
	RemoteManager& operator=(RemoteManager&) = delete;

private:
	//void SendNormalCommand(int commandId);
	//void SendSpecialCommand(int commandId);
	void SendCommand(CmdAttributeType type, CommandId id);
};

#endif