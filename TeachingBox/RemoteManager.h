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
#include "..\DataStream\DataStream.h"


class RemoteManager
{
	friend SingleTon<RemoteManager>;

public:
	static RemoteManager* GetInstance();

	template<typename T>
	void SendCommand(CmdAttributeType type, CommandId id, T value);

	template<typename T>
	void SendSpecialCommand(CommandId id, T value);


	void SendCommand(const DataStream& stream);
	void SendCommandToGetPosition();
	void SendCommandToGetPose();
	void SendEndCommand();
	void SendSpecialCommand(CommandId id);
	void SendStopCommand();

private:
	RemoteManager();
	~RemoteManager();
	RemoteManager(const RemoteManager&) = delete;
	RemoteManager& operator=(RemoteManager&) = delete;

private:
	tTeachCmdAttribute GetAttribute(CmdAttributeType type, CommandId id);
	void SendCommand(CmdAttributeType type, CommandId id);
};

template<typename T>
void RemoteManager::SendCommand(CmdAttributeType type, CommandId id, T value)
{
	DataStream stream;
	auto attribute = GetAttribute(type, id);
	stream << attribute;
	stream << value;
	stream.Seek(0);

	attribute.m_length = stream.Length();
	stream.Seek(0);
	stream << attribute;
	stream.Seek(0);

	SendCommand(stream);
}

template<typename T>
void RemoteManager::SendSpecialCommand(CommandId id, T value)
{
	SendCommand(CmdAttributeType::CMD_ATTRIBUTE_SPECIAL_COMMAND, id, value);
}

#endif