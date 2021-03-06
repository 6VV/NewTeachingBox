﻿#ifndef _TEACHING_BOX_INTERPRETER_CONTEXT_H_
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
	enum ExecuteState
	{
		EXECUTING,
		STOP,
	};

	struct FunctionInfo
	{
		FunctionInfo(const QString& functionName="", int lineNumber=1)
			:functionName(functionName)
			, lineNumber(lineNumber)
		{}
		QString functionName="";
		int lineNumber = 1;
	};

public:
	//TAstNode* CurrentProgramNode() const;
	void ClearFunctionInfo();

	TAstNode* GetNextNode() const;
	ExecuteMode GetExecuteMode() const;
	ExecuteState GetExecuteState() const;
	std::shared_ptr<TAstNode> GetRootNode() const;
	int GetPCLine() const;
	QString GetProgramExecuting() const;
	QString GetProgramLoading() const;

	bool IsAllowSendCommandData() const;
	void IsAllowSendCommandData(bool enabled);

	void PushFunctionInfo(const FunctionInfo& funInfo);
	FunctionInfo PopFunctionInfo();

	//void SetCurrentScope(QString val);
	void SetNextNode(TAstNode* nextNode);
	void SetExecuteMode(ExecuteMode mode);
	void SetExecuteState(ExecuteState mode);
	void SetRootNode(std::shared_ptr<TAstNode> rootNode);
	void SetPCLine(int val);
	void SetProgramExecuting(const QString& program);
	void SetProgramLoading(const QString& program);

private:
	ExecuteMode m_executeMode = ExecuteMode::AUTO;	/*执行模式*/
	ExecuteState m_executeState = ExecuteState::STOP;	/*执行状态*/
	QString m_programExecuting{};	/*当前执行程序*/
	QString m_programLoading{};	/*正在加载的程序，与正在执行的程序不同，此处仅用于解析过程*/

	std::shared_ptr<TAstNode> m_rootNode{ nullptr };	/*语法树根节点*/
	TAstNode*  m_nextNode = nullptr;	/*下一节点*/
	int m_pcLine = -1;	/*执行行*/
	std::vector<FunctionInfo> m_functionInformations{};

	bool m_isAllowSendData = false;
};

#endif