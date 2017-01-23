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
	/*************************************************
	//  Method:        void AddVariate(std::shared_ptr<TVariate> variate)
	//  Description:   添加变量
	//  Author:        刘巍 
	//  Date:          2016/12/07
	//  Returns:       void
	//  Parameter:     std::shared_ptr<TVariate> variate：将要添加的变量
	//  History:       
	*************************************************/
	void AddVariate(std::shared_ptr<TVariate> variate);

	/*************************************************
	//  Method:        void AddScope(const QString& scope)
	//  Description:   添加作用域节点，若已存在该作用域，则返回
	//  Author:        刘巍 
	//  Date:          2016/12/07
	//  Returns:       void
	//  Parameter:     const QString& scope：作用域名
	//  History:       
	*************************************************/
	void AddScope(const QString& scope);

	/*************************************************
	//  Method:        void Clear()
	//  Description:   清除所用项目作用域，以及初始作用域中的所有变量
	//  Author:        刘巍 
	//  Date:          2016/12/07
	//  Returns:       
	//  Parameter:     
	//  History:       
	*************************************************/
	void Clear();

	/*************************************************
	//  Method:        void DeleteVariate(const QString& scope, const QString& name)
	//  Description:   删除变量
	//  Author:        刘巍 
	//  Date:          2016/12/07
	//  Returns:       void
	//  Parameter:     const QString& scope:变量作用域
			const QString& name：变量名
	//  History:       
	*************************************************/
	void DeleteVariate(const QString& scope, const QString& name);

	/*************************************************
	//  Method:        QVector<std::shared_ptr<TVariate>> GetVariatesScollUp(const QString& scope) const;
	//  Description:   从特定作用域开始，向上查找所有有效变量，不包括同名变量
	//  Author:        刘巍
	//  Date:          2017/01/13
	//  Returns:       QVector<std::shared_ptr<TVariate>>：当前作用域的所有有效变量
	//  Parameter:     const QString& scope：查找的起始作用域
	//  History:
	*************************************************/
	QVector<std::shared_ptr<TVariate>> GetAvailableVariatesScollUp(const QString& scope) const;

	/*获取scope作用域及以上作用域typeName类型的变量，不包括重名变量*/
	QVector<std::shared_ptr<TVariate>> GetAvailableVariatesScollUp(const QString& scope, const QString& typeName);

	/*************************************************
	//  Method:        QMap<QString, QVector<TVariate*>> GetVariatesMapScollUp(const QString& scope) const
	//  Description:   获取从某作用域起开始向上，所有变量的集合,包括不同作用域的重名变量
	//  Author:        刘巍
	//  Date:          2016/12/07
	//  Returns:       QMap<QString, QVector<TVariate*>>：变量集合
	//  Parameter:     const QString& scope：起始作用域
	//  History:
	*************************************************/
	QMap<QString, QVector<std::shared_ptr<TVariate>>> GetAllVariatesMapScollUp(const QString& scope) const;

	/*获取所有作用域内typeName类型变量*/
	QVector<std::shared_ptr<TVariate>> GetAllVariates(const QString& typeName) const;

	/*************************************************
	//  Method:        std::shared_ptr<TVariate> GetVariate(const QString& scope, const QString& name) const
	//  Description:   查找特定作用内的变量，若未找到则返回nullptr
	//  Author:        刘巍 
	//  Date:          2016/12/07
	//  Returns:       std::shared_ptr<TVariate>：找到的变量
	//  Parameter:     const QString& scope：作用域
			const QString& name：变量名
	//  History:       
	*************************************************/
	std::shared_ptr<TVariate> GetVariate(const QString& scope, const QString& name) const;

	/*************************************************
	//  Method:        std::shared_ptr<TVariate> FindVariateScollUp(const QString& scope, const QString& name) const
	//  Description:   从作用域向上翻滚查找变量
	//  Author:        刘巍 
	//  Date:          2016/12/07
	//  Returns:       std::shared_ptr<TVariate>：查找到的变量指针
	//  Parameter:     const QString& scope：作用域；
			const QString& name：变量名
	//  History:       
	*************************************************/
	std::shared_ptr<TVariate> GetVariateScollUp(const QString& scope, const QString& name) const;

	/*************************************************
	//  Method:        QVector<std::shared_ptr<TVariate>> GetAllVariateFromScope(const QString& scope) const
	//  Description:   从作用域中获取所有变量
	//  Author:        刘巍 
	//  Date:          2016/12/07
	//  Returns:       QVector<std::shared_ptr<TVariate>>：变量集合
	//  Parameter:     const QString& scope：作用域名
	//  History:       
	*************************************************/
	QVector<std::shared_ptr<TVariate>> GetVariates(const QString& scope) const;

	/*获取scope作用域typeName类型的变量*/
	QVector<std::shared_ptr<TVariate>> GetVariates(const QString& scope, const QString& typeName);

	/*************************************************
	//  Method:        void UpdateVariate(std::shared_ptr<TVariate> newVariate)
	//  Description:   更新变量
	//  Author:        刘巍 
	//  Date:          2016/12/07
	//  Returns:       void
	//  Parameter:     std::shared_ptr<TVariate> newVariate：新变量的指针
	//  History:       
	*************************************************/
	void UpdateVariate(std::shared_ptr<TVariate> newVariate);

private:
	void AddProjectScopeNode(const QString& nodeName);
	void AddProgramScopeNode(const QString& nodeName);
	void AddScopeWithoutCheck(const QString& scope);	/*不经检查直接添加作用域节点*/

	void InitScope();	/*初始化作用域，包括系统作用域、协作作用域、全局作用域*/

	void PushScopeVariates(std::shared_ptr<TVariateScopeNode> scopeNode, QVector<std::shared_ptr<TVariate>>& desVariates,const QString& typeName) const;

private:
	std::shared_ptr<TVariateScopeNode> m_rootNode;
};



#endif