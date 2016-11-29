#ifndef _TEACHING_BOX_T_VARIATE_CONTEXT_H_
#define _TEACHING_BOX_T_VARIATE_CONTEXT_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TVariateContext.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/29
//  Description:    变量环境，单例模式，用于记录当前所有可用的变量，并提供对变量的操作
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/11/29
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <memory>
#include "TVariateScopeNode.h"

class TVariate;

class TVariateContext
{
public:
	static TVariateContext* GetInstance();

private:
	TVariateContext();
	TVariateContext(const TVariateContext&) = delete;
	TVariateContext& operator=(const TVariateContext&) = delete;
	~TVariateContext() = default;

public:
	void AddVariate(std::shared_ptr<TVariate> variate);

private:
	void AddProjectScopeNode(const QString& nodeName);
	void AddProgramScopeNode(const QString& nodeName);

private:
	std::shared_ptr<TVariateScopeNode> m_rootNode;
};



#endif