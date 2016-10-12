#include "stdafx.h"
#include "InterpreterContext.h"
#include "TTokenWithValue.h"
#include "TAstNode.h"


//QString InterpreterContext::GetCurrentScope() const
//{
//	return m_currentScope;
//}

TAstNode* InterpreterContext::GetNextNode() const
{
	return m_nextNode;
}


InterpreterContext::ExecuteMode InterpreterContext::GetExecuteMode() const
{
	return m_executeMode;
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

//void InterpreterContext::SetCurrentScope(QString val)
//{
//	m_currentScope = val;
//}

void InterpreterContext::SetNextNode(TAstNode* nextNode)
{
	m_nextNode = nextNode;
}


void InterpreterContext::SetExecuteMode(ExecuteMode mode)
{
	m_executeMode = mode;
}

void InterpreterContext::SetRootNode(std::shared_ptr<TAstNode> rootNode)
{
	m_rootNode = rootNode;
}

void InterpreterContext::IsAllowExecute(bool isExecuting)
{
	m_isAllowExecute = isExecuting;
}

bool InterpreterContext::IsAllowExecute() const
{
	return m_isAllowExecute;
}

int InterpreterContext::GetLineNumber() const
{
	return m_lineNumber;
}

void InterpreterContext::SetLineNumber(int val)
{
	m_lineNumber = val;
}
