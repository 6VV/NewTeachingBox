#include "stdafx.h"
#include "InterpreterContext.h"



QString InterpreterContext::GetCurrentScope() const
{
	return m_currentScope;
}

TAstNode* InterpreterContext::GetNextNode() const
{
	return m_nextNode;
}

TAstNode* InterpreterContext::GetCurrentProgramNode() const
{
	return m_currentProgramNode;
}

InterpreterContext::ExecuteMode InterpreterContext::GetExecuteMode() const
{
	return m_executeMode;
}

void InterpreterContext::SetCurrentScope(QString val)
{
	m_currentScope = val;
}

void InterpreterContext::SetNextNode(TAstNode* nextNode)
{
	m_nextNode = nextNode;
}

void InterpreterContext::SetCurrentProgramNode(const TAstNode* programNode)
{
	m_currentProgramNode = const_cast<TAstNode*>(programNode);
}

void InterpreterContext::SetExecuteMode(ExecuteMode mode)
{
	m_executeMode = mode;
}

void InterpreterContext::IsExecuting(bool isExecuting)
{
	m_isExecuting = isExecuting;
}

bool InterpreterContext::IsExecuting() const
{
	return m_isExecuting;
}
