#include "stdafx.h"
#include "RemoteManager.h"
#include "DataStruct.h"
#include "QDebug"
#include "TcpAdapter.h"
#include "Context.h"


RemoteManager* RemoteManager::GetInstance()
{
	return SingleTon<RemoteManager>::GetInstance();
}

void RemoteManager::SendMovlCommand(const char* commandData, int commandLength, int lineNumber, long long programAddress)
{
	Context::interpreterContext.IsAllowSendCommandData(false);

	m_tcpAdapter->SendData(std::move(ContructNormalCommand(COMMAND_ID::MOVL, commandData, commandLength, lineNumber, programAddress)));
}

void RemoteManager::SendStopCommand()
{
	m_tcpAdapter->SendData(std::move(ContructSpecialCommand(COMMAND_ID::STOP_EXECUTE)));
}


void RemoteManager::SendEndCommand()
{
	m_tcpAdapter->SendData(std::move(ContructNormalCommand(COMMAND_ID::END)));
}

RemoteManager::RemoteManager() :m_tcpAdapter(new TcpAdapter())
{

}

RemoteManager::~RemoteManager()
{

}

inline
void RemoteManager::AddLock(char* head, int& offset)
{
	*(head + offset) = 0;
	++offset;
}

inline
void RemoteManager::AddNormalCommandAttribute(char* head, int& offset, int commandId, int commandLength, int lineNumber, long long programAddress)
{
	tTeachCmdAttribute attribute;
	attribute.m_length = 1 + sizeof(tTeachCmdAttribute) + commandLength;
	attribute.m_ID = commandId;
	attribute.m_type = CmdAttributeType::CMD_ATTRIBUTE_NORMAL_COMMAND;
	attribute.m_LineNumber = lineNumber;
	attribute.m_programAddress = programAddress;

	*(tTeachCmdAttribute*)(head + offset) = attribute;
	offset += sizeof(tTeachCmdAttribute);
}

inline
void RemoteManager::AddCommand(char* head, int& offset, const char* command,int commandLength)
{
	for (int i = 0; i < commandLength;++i,++offset)
	{
		*(head + offset) = *(command + i);
	}
}

QByteArray RemoteManager::ContructNormalCommand(int commandId, const char* commandData, int commandLength, int lineNumber, long long programAddress)
{
	static const int LENGTH = 1024;
	char result[LENGTH];
	int offset = 0;

	AddLock(result, offset);
	AddNormalCommandAttribute(result, offset, commandId, commandLength,lineNumber,programAddress);
	AddCommand(result, offset, commandData,commandLength);

	return QByteArray(result, LENGTH);
}

QByteArray RemoteManager::ContructNormalCommand(int commandId)
{
	QByteArray result;
	result.append('\0');

	tTeachCmdAttribute attribute;
	attribute.m_type = CmdAttributeType::CMD_ATTRIBUTE_NORMAL_COMMAND;
	attribute.m_length = 1 + sizeof(tTeachCmdAttribute);
	attribute.m_ID = commandId;
	result.append((char*)&attribute, sizeof(tTeachCmdAttribute));

	return std::move(result);
}

QByteArray RemoteManager::ContructSpecialCommand(int commandId)
{
	QByteArray result;
	result.append('\0');
	
	tTeachCmdAttribute attribute;
	attribute.m_type = CmdAttributeType::CMD_ATTRIBUTE_SPECIAL_COMMAND;
	attribute.m_length = 1+sizeof(tTeachCmdAttribute);
	attribute.m_ID = commandId;
	result.append((char*)&attribute, sizeof(tTeachCmdAttribute));

	return std::move(result);
}
