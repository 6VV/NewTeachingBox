#ifndef _TEACHING_BOX_INTERPRETER_CONTEXT_H_
#define _TEACHING_BOX_INTERPRETER_CONTEXT_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    InterpreterContext.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/09/09
//  Description:	记录解释器环境变量，包括当前节点、作用域等
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/09/09
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QString"

class TAstNode;

class InterpreterContext
{
public:
	enum ExecuteMode
	{
		AUTO,
		STEP,
		MANUAL,
	};

public:
	QString GetCurrentScope() const;
	TAstNode* GetNextNode() const;
	TAstNode* GetCurrentProgramNode() const;
	ExecuteMode GetExecuteMode() const;
	bool IsExecuting() const;

	void SetCurrentScope(QString val);
	void SetNextNode(TAstNode* nextNode);
	void SetCurrentProgramNode(const TAstNode* programNode);
	void SetExecuteMode(ExecuteMode mode);
	void IsExecuting(bool isExecuting);

private:
	ExecuteMode m_executeMode=ExecuteMode::AUTO;
	QString m_currentScope;
	TAstNode*  m_nextNode;
	TAstNode* m_currentProgramNode;

	bool m_isExecuting = false;
};

#endif