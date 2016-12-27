#include "stdafx.h"
#include "RemoteManager.h"
#include "DataStruct.h"
#include "QDebug"
#include "TcpAdapter.h"
#include "Context.h"
#include "RemoteAdapterFactory.h"
#include "..\DataStream\DataStream.h"


RemoteManager* RemoteManager::GetInstance()
{
	return SingleTon<RemoteManager>::GetInstance();
}


void RemoteManager::SendCommand(const DataStream& stream)
{
	static const int LENGTH = 1024;
	char result[LENGTH];

	result[0] = '\0';
	stream.ReadRawBytes(result + 1, stream.Length());

	RemoteAdapterFactory::GetRemoteAdapter()->SendData(QByteArray(result, LENGTH));

}

void RemoteManager::SendCommand(CmdAttributeType type, CommandId id)
{
	tTeachCmdAttribute attribute;
	attribute.m_type = type;
	attribute.m_length = 1 + sizeof(tTeachCmdAttribute);
	attribute.m_ID = id;

	DataStream result;
	result << attribute;
	result.Seek(0);

	SendCommand(result);
}


void RemoteManager::SendCommandToGetPose()
{
	SendCommand(CMD_ATTRIBUTE_SPECIAL_COMMAND, CommandId::ROBOT_POSE_EULER);
}

void RemoteManager::SendStopCommand()
{
	SendCommand(CmdAttributeType::CMD_ATTRIBUTE_SPECIAL_COMMAND,CommandId::STOP_EXECUTE);
}


void RemoteManager::SendEndCommand()
{
	SendCommand(CmdAttributeType::CMD_ATTRIBUTE_NORMAL_COMMAND,CommandId::END);
}

void RemoteManager::SendCommandToGetPosition()
{
	SendCommand(CMD_ATTRIBUTE_SPECIAL_COMMAND, CommandId::ROBOT_POSITION);
}

RemoteManager::RemoteManager()
{

}

RemoteManager::~RemoteManager()
{

}
//
//void RemoteManager::SendNormalCommand(int commandId)
//{
//	tTeachCmdAttribute attribute;
//	attribute.m_type = CmdAttributeType::CMD_ATTRIBUTE_NORMAL_COMMAND;
//	attribute.m_length = 1 + sizeof(tTeachCmdAttribute);
//	attribute.m_ID = commandId;
//
//	DataStream result;
//	result << attribute;
//	result.Seek(0);
//
//	SendCommand(result);
//}
//
//void RemoteManager::SendSpecialCommand(int commandId)
//{
//	tTeachCmdAttribute attribute;
//	attribute.m_type = CmdAttributeType::CMD_ATTRIBUTE_SPECIAL_COMMAND;
//	attribute.m_length = 1 + sizeof(tTeachCmdAttribute);
//	attribute.m_ID = commandId;
//
//	DataStream result;
//	result << attribute;
//	result.Seek(0);
//
//	SendCommand(result);
//}
