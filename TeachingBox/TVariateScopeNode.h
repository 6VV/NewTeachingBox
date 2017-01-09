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
#include <memory>

class TVariate;

class TVariateScopeNode
{
public:
	TVariateScopeNode(const QString& socpeName="");

	void AddChild(std::shared_ptr<TVariateScopeNode> node);
	void AddOrUpdateVariate(std::shared_ptr<TVariate> variate);

	void DeleteVariate(const QString& name);

	QVector<std::shared_ptr<TVariate>> GetVariates() const;
	QString GetName() const;
	TVariateScopeNode* GetParentNode() const;

	std::shared_ptr<TVariateScopeNode> FindScope(const QString& scopeName) const;
	std::shared_ptr<TVariate> FindVariate(const QString& name) const;

private:
	void SetParentNode(TVariateScopeNode* parentNode);

private:
	QString m_name;
	TVariateScopeNode* m_parentNode=nullptr;
	QMap<QString, std::shared_ptr<TVariateScopeNode>> m_childScopes;
	QMap<QString, std::shared_ptr<TVariate>> m_variates;
};

#endif