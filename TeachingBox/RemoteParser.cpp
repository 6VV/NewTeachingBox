﻿#include "stdafx.h"
#include "RemoteParser.h"
#include "DataStruct.h"
#include "TAstNode.h"
#include "TTokenWithValue.h"
#include "Context.h"
#include "InterpreterManager.h"
#include "CodeEditor.h"
#include "RemoteFeedbackController.h"
#include "TAstNodeProgram.h"
#include <assert.h>
#include "..\DataStream\DataStream.h"
#include <xutility>


RemoteParser::RemoteParser(QObject* parent/*=nullptr*/)
	:QObject(parent)
{

}

RemoteParser::~RemoteParser()
{

}

void RemoteParser::ParseCommands(QByteArray& commands) const
{
	QList<QByteArray> commandList;
	SplitCommand(commandList, commands);

	for each (auto cmd in commandList)
	{
		ParseOneCommand(cmd);
	}
}

void RemoteParser::ParseOneCommand(QByteArray& command) const
{
	DataStream stream;
	stream.WriteRawBytes(command.data() , command.length());
	//tTeachCmdAttribute attribute = GetAttribute(command.data());
	stream.Seek(1);
	tTeachCmdAttribute attribute;
	stream >> attribute;

	switch (attribute.m_ID)
	{
	case CommandId::NORMAL_COMMAND:
	{
		SendNextCommand();
	}break;
	case CommandId::NORMAL_COMMAND_FEEDBACK:
	{
		RefreshLineNumber(attribute);
	}break;
	case CommandId::ROBOT_POSITION:
	{
		tAxesAllPositions position;
		stream >> position;
		RemoteFeedbackController::GetInstance()->OnReseivePosition(position);
	}break;
	default:
		break;
	}
}

tTeachCmdAttribute RemoteParser::GetAttribute(char* command) const
{
	DataStream stream;
	stream.WriteRawBytes(command, COMMAND_HEAD_LENGTH);
	stream.Seek(1);
	tTeachCmdAttribute attribute;
	stream >> attribute;
	return std::move(attribute);
}

void RemoteParser::SplitCommand(QList<QByteArray>& commandList, QByteArray& commands) const
{
	int length = 0;
	while (commands.size() > 0)
	{
		length = GetAttribute(commands.data()).m_length;
		if (length <= 0 || length > commands.size())
		{
			break;
		}
		QByteArray newCommand = commands.left(length);
		commandList.append(newCommand);
		commands.remove(0, length);
	}
}

void RemoteParser::SendNextCommand() const
{
	Context::interpreterContext.IsAllowSendCommandData(true);
	InterpreterManager::GetInstance()->ExecuteNextCommand();
}

void RemoteParser::RefreshLineNumber(const tTeachCmdAttribute& attribute) const
{
	auto rootNode = Context::interpreterContext.GetRootNode();
	auto childNode = rootNode->GetFirstChild();
	int id = attribute.m_programId;

	QString program{};
	while (childNode!=nullptr)
	{
		assert(typeid(*childNode) == typeid(TAstNodeProgram));
		auto programNode = std::dynamic_pointer_cast<TAstNodeProgram>(childNode);
		if (programNode->GetId()==id)
		{
			program = programNode->GetToken()->Name();
			break;
		}
		childNode = childNode->GetSibling();
	}

	if (program.size()==0)
	{
		return;
	}
	int lineNumber = attribute.m_LineNumber;

	CodeEditor::GetInstance()->HighlightPCLine(program, lineNumber);
	//RemoteFeedbackController::GetInstance()->RefreshLineNumber(program, lineNumber);

}

