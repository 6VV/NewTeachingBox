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

//void RemoteManager::SendCommand(CmdAttributeType type, CommandId id)
//{
//
//}

void RemoteManager::SendStopCommand()
{
	SendSpecialCommand(CommandId::STOP_EXECUTE);
}


void RemoteManager::SendEndCommand()
{
	SendNormalCommand(CommandId::END);
}

RemoteManager::RemoteManager()
{

}

RemoteManager::~RemoteManager()
{

}

void RemoteManager::SendNormalCommand(int commandId)
{
	tTeachCmdAttribute attribute;
	attribute.m_type = CmdAttributeType::CMD_ATTRIBUTE_NORMAL_COMMAND;
	attribute.m_length = 1 + sizeof(tTeachCmdAttribute);
	attribute.m_ID = commandId;

	DataStream result;
	result << attribute;
	result.Seek(0);

	SendCommand(result);
}

void RemoteManager::SendSpecialCommand(int commandId)
{
	tTeachCmdAttribute attribute;
	attribute.m_type = CmdAttributeType::CMD_ATTRIBUTE_SPECIAL_COMMAND;
	attribute.m_length = 1 + sizeof(tTeachCmdAttribute);
	attribute.m_ID = commandId;

	DataStream result;
	result << attribute;
	result.Seek(0);

	SendCommand(result);
}
