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


tTeachCmdAttribute RemoteManager::GetAttribute(CmdAttributeType type, CommandId id)
{
	tTeachCmdAttribute attribute;
	attribute.m_type = type;
	attribute.m_length =sizeof(tTeachCmdAttribute);
	attribute.m_ID = id;

	return attribute;
}

void RemoteManager::SendCommand(const DataStream& stream)
{
	char result[COMMAND_MAX_LENGTH];

	stream.ReadRawBytes(result, stream.Length());

	RemoteAdapterFactory::GetRemoteAdapter()->SendData(QByteArray(result, COMMAND_MAX_LENGTH));

}

void RemoteManager::SendCommand(CmdAttributeType type, CommandId id)
{
	DataStream result;
	result << GetAttribute(type, id);
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

void RemoteManager::SendSpecialCommand(CommandId id)
{
	SendCommand(CmdAttributeType::CMD_ATTRIBUTE_SPECIAL_COMMAND, id);
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
