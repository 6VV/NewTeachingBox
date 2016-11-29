#include "stdafx.h"
#include "RemoteParser.h"
#include "DataStruct.h"
#include "TAstNode.h"
#include "TTokenWithValue.h"
#include "Context.h"
#include "InterpreterManager.h"
#include "CodeEditor.h"
#include "RemoteFeedbackController.h"


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
	tTeachCmdAttribute* attribute = GetAttribute(command.data());

	switch (attribute->m_ID)
	{
	case COMMAND_ID::NORMAL_COMMAND:
	{
		SendNextCommand();
	}break;
	case COMMAND_ID::NORMAL_COMMAND_FEEDBACK:
	{
		RefreshLineNumber(*attribute);
	}break;
	case COMMAND_ID::ROBOT_POSITION:
	{
		OnReceivePosition(command);
	}break;
	default:
		break;
	}
}

tTeachCmdAttribute* RemoteParser::GetAttribute(char* command) const
{
	return (tTeachCmdAttribute*)(command + LOCK_LENGTH);
}

void RemoteParser::SplitCommand(QList<QByteArray>& commandList, QByteArray& commands) const
{
	int length = 0;
	while (commands.size() > 0)
	{
		length = GetAttribute(commands.data())->m_length;
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
	auto program = reinterpret_cast<TAstNode*>(attribute.m_programAddress)->GetToken()->Name();
	int lineNumber = attribute.m_LineNumber;

	CodeEditor::GetInstance()->HighlightPCLine(program, lineNumber);
	//RemoteFeedbackController::GetInstance()->RefreshLineNumber(program, lineNumber);

}

void RemoteParser::OnReceivePosition(QByteArray& command) const
{
	tAxesAllPositions position = *(reinterpret_cast<tAxesAllPositions*>(command.data() + sizeof(tTeachCmdAttribute)));
	RemoteFeedbackController::GetInstance()->OnReseivePosition(position);
}
