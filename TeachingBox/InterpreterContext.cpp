#include "stdafx.h"
#include "InterpreterContext.h"
#include "TTokenWithValue.h"
#include "TAstNode.h"
#include "TeachingBoxBroadcast.h"


void InterpreterContext::ClearFunctionInfo()
{
	m_functionInformations.clear();
}

//TAstNode* InterpreterContext::CurrentProgramNode() const
//{
//	if (m_nextNode == nullptr || m_nextNode->GetParentNode()==nullptr)
//	{
//		return nullptr;
//	}
//
//	auto result = m_nextNode;
//
//	while (result->GetParentNode()->GetParentNode() != nullptr)
//	{
//		result = result->GetParentNode();
//	}
//
//	return result;
//
//}

TAstNode* InterpreterContext::GetNextNode() const
{
	return m_nextNode;
}


InterpreterContext::ExecuteMode InterpreterContext::GetExecuteMode() const
{
	return m_executeMode;
}

InterpreterContext::ExecuteState InterpreterContext::GetExecuteState() const
{
	return m_executeState;
}

QString InterpreterContext::GetProgramExecuting() const
{
	return m_programExecuting;
}

QString InterpreterContext::GetProgramLoading() const
{
	return m_programLoading;
}

std::shared_ptr<TAstNode> InterpreterContext::GetRootNode() const
{
	return m_rootNode;
}

void InterpreterContext::IsAllowSendCommandData(bool enabled)
{
	m_isAllowSendData = enabled;
}

bool InterpreterContext::IsAllowSendCommandData() const
{
	return m_isAllowSendData;
}

void InterpreterContext::PushFunctionInfo(const FunctionInfo& funInfo)
{
	m_functionInformations.push_back(funInfo);
}

InterpreterContext::FunctionInfo InterpreterContext::PopFunctionInfo()
{
	if (m_functionInformations.size()==0)
	{
		return{};
	}
	auto funInfo= m_functionInformations.back();
	m_functionInformations.pop_back();

	return funInfo;
}

void InterpreterContext::SetNextNode(TAstNode* nextNode)
{
	m_nextNode = nextNode;
}


void InterpreterContext::SetExecuteMode(ExecuteMode mode)
{
	m_executeMode = mode;
	emit(TeachingBoxBroadcast::GetInstance()->ExecuteModeChanged(m_executeMode));
}

void InterpreterContext::SetExecuteState(ExecuteState state)
{
	m_executeState = state;
	emit(TeachingBoxBroadcast::GetInstance()->ExecuteStateChanged(m_executeState));
}

void InterpreterContext::SetProgramExecuting(const QString& program)
{
	m_programExecuting = program;
}

void InterpreterContext::SetProgramLoading(const QString& program)
{
	m_programLoading = program;
}

void InterpreterContext::SetRootNode(std::shared_ptr<TAstNode> rootNode)
{
	m_rootNode = rootNode;
}

int InterpreterContext::GetPCLine() const
{
	return m_pcLine;
}

void InterpreterContext::SetPCLine(int val)
{
	m_pcLine = val;
}
