﻿#include "stdafx.h"
#include "TInterpreterThread.h"
#include "Context.h"
#include "TAstNode.h"
#include "RemoteManager.h"


void TInterpreterThread::SlotAutoExecute()
{
	SlotExecuteNextCommand();
}

void TInterpreterThread::SlotStepExecute()
{
	SlotExecuteNextCommand();

	Context::interpreterContext.SetExecuteState(InterpreterContext::STOP);	/*执行一条指令后，禁止执行之后语句 */

	SendEndCommand();
}

void TInterpreterThread::SlotStopExecute()
{
	RemoteManager::GetInstance()->SendStopCommand();
}


void TInterpreterThread::SlotExecuteNextCommand()
{
	auto nextNode = Context::interpreterContext.GetNextNode();

	while (nextNode != nullptr && Context::interpreterContext.GetExecuteState()==InterpreterContext::EXECUTING && Context::interpreterContext.IsAllowSendCommandData())
	{
		nextNode->Execute();
		nextNode = Context::interpreterContext.GetNextNode();
	}
	if (nextNode==nullptr)
	{
		Context::interpreterContext.SetExecuteState(InterpreterContext::STOP);
	}
}

inline
void TInterpreterThread::SendEndCommand()
{
	RemoteManager::GetInstance()->SendEndCommand();
}
