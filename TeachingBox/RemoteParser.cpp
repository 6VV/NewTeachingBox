#include "stdafx.h"
#include "RemoteParser.h"
#include "DataStruct.h"
#include "TAstNode.h"
#include "TTokenWithValue.h"
#include "Context.h"
#include "InterpreterManager.h"
#include "CodeEditor.h"


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
		OnResivePosition(command);
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
	qDebug() << "Send Next Command";
	Context::interpreterContext.IsAllowSendCommandData(true);
	InterpreterManager::GetInstance()->ExecuteNextCommand();
	//CInterpreterManager::GetInstance()->InterpreteNextCommand();
}

void RemoteParser::RefreshLineNumber(const tTeachCmdAttribute& attribute) const
{
	auto program=dynamic_cast<TTokenWithValue<QString>*>(
		reinterpret_cast<TAstNode*>(attribute.m_programAddress)->GetToken().get())->GetValue();
	int lineNumber = attribute.m_LineNumber;

	CodeEditor::GetInstance()->HighlightPCLine(program, lineNumber);
	//TAstNode* programNode = (TAstNode*)attribute.m_programAddress;
	//CScreenProject::GetInstance()->RefreshProgramLineNumber(
	//	dynamic_cast<TTokenWithValue<QString>*>(programNode->GetToken().get())->GetValue(), attribute.m_LineNumber);
}

void RemoteParser::OnResivePosition(QByteArray& command) const
{
	command;
	//tAxesAllPositions position;
	//position = *(tAxesAllPositions*)(command.data() + COMMAND_HEAD_LENGTH);
	//emit(SignalOnResivePosition(position));
}
