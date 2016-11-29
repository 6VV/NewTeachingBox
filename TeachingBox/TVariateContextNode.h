#ifndef _TEACHING_BOX_T_VARIATE_CONTEXT_NODE_H_
#define _TEACHING_BOX_T_VARIATE_CONTEXT_NODE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TVariateContextNode.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/29
//  Description:    存储某个作用域内的所有变量及子作用域
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/11/29
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QVector"
#include "QMap"

class TVariate;

class TVariateContextNode
{
public:
	void AddChild(std::shared_ptr<TVariateContextNode> node);
	void AddVariate(std::shared_ptr<TVariate> variate);

private:
	QVector<std::shared_ptr<TVariateContextNode>> m_childScopes;
	QMap<QString, std::shared_ptr<TVariate>> m_variates;
};

#endif