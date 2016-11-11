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
	//QString GetCurrentScope() const;
	TAstNode* CurrentProgramNode() const;
	TAstNode* GetNextNode() const;
	ExecuteMode GetExecuteMode() const;
	std::shared_ptr<TAstNode> GetRootNode() const;
	int GetLineNumber() const;

	bool IsAllowExecute() const;
	void IsAllowExecute(bool isExecuting);
	bool IsAllowSendCommandData() const;
	void IsAllowSendCommandData(bool enabled);

	//void SetCurrentScope(QString val);
	void SetNextNode(TAstNode* nextNode);
	void SetExecuteMode(ExecuteMode mode);
	void SetRootNode(std::shared_ptr<TAstNode> rootNode);
	void SetLineNumber(int val);


private:
	ExecuteMode m_executeMode=ExecuteMode::AUTO;
	std::shared_ptr<TAstNode> m_rootNode{ nullptr };
	TAstNode*  m_nextNode=nullptr;

	int m_lineNumber=1;

	bool m_isAllowExecute = false;
	bool m_isAllowSendData = false;
};

#endif