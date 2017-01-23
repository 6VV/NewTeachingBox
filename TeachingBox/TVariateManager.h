#ifndef _TEACHING_BOX_T_VARIATE_MANAGER_H_
#define _TEACHING_BOX_T_VARIATE_MANAGER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TVariateManager.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/09/05
//  Description:	变量管理器，用于管理变量的添加、删除、修改，包括内存及数据库中的变量
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/09/05
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "SingleTon.h"
#include "QHash"
#include "QString"
#include <memory>
#include "QVector"
#include "QObject"

class TVariate;
class TScope;

class TVariateManager:public QObject
{
	friend SingleTon<TVariateManager>;

	Q_OBJECT

private:
	typedef QHash<QString, QHash<QString, TVariate*>> VariateMAP;

public:
	static TVariateManager* GetInstance();

private:
	TVariateManager();
	TVariateManager(const TVariateManager&);

	TVariateManager& operator=(const TVariateManager&);
	~TVariateManager();

public:
	void AddVariate(std::shared_ptr<TVariate> variate);

	void DeleteVariate(const QString& scope, const QString& name);
	void DeleteProjectVariates(const QStringList& names);
	void DeleteProgramVariates(const QString& program);

	/*************************************************
	//  Method:        QVector<std::shared_ptr<TVariate>> GetVariatesScollUp(const QString& scope);
	//  Description:   获取某作用域及以上所有作用域中的变量集合，不包括重名变量
	//  Author:        刘巍 
	//  Date:          2017/01/13
	//  Returns:       QVector<std::shared_ptr<TVariate>>：作用域内所有有效变量集合，不包括重名变量
	//  Parameter:     const QString& scope：查询的起始作用域
	//  History:       
	*************************************************/
	QVector<std::shared_ptr<TVariate>> GetAvailableVariatesScollUp(const QString& scope);

	/*************************************************
	//  Method:        QMap<QString, QVector<TVariate*>> GetVariatesMapScollUp(const QString& scope)
	//  Description:   获取某作用域及以上所有作用域中的变量集合，包括重名变量
	//  Author:        刘巍 
	//  Date:          2016/11/16
	//  Returns:       QMap<QString, QVector<TVariate*>>：作用域及其变量集合，QString为作用域，QVector<TVariate*>为变量集合
	//  Parameter:     const QString& scope：查询的起始作用域
	//  History:
	*************************************************/
	QMap<QString, QVector<std::shared_ptr<TVariate>>> GetAllVariatesMapScollUp(const QString& scope);

	/*获取所有typeName类型变量*/
	QVector<std::shared_ptr<TVariate>> GetAllVariates(const QString& typeName);

	/*************************************************
	//  Method:        QVector<TVariate*> GetVariatesFromScope(const QString& scope)
	//  Description:   获取特定作用域内的所有变量
	//  Author:        刘巍
	//  Date:          2016/11/16
	//  Returns:       QVector<TVariate*>：变量集合
	//  Parameter:     const QString& scope：作用域名
	//  History:
	*************************************************/
	QVector<std::shared_ptr<TVariate>> GetVariatesFromScope(const QString& scope);

	/*************************************************
	//  Method:        TVariate* GetVariate(const QString& scope, const QString& name)
	//  Description:   查找特定作用域内的变量，若未找到则返回nullptr
	//  Author:        刘巍
	//  Date:          2016/11/16
	//  Returns:       TVariate* :查找到的变量指针，若未找到，为nullptr
	//  Parameter:     const QString& scope:查找的作用域
	//		const QString& name:变量名
	//  History:
	*************************************************/
	std::shared_ptr<TVariate> GetVariate(const QString& scope, const QString& name);

	/*************************************************
	//  Method:        TVariate* GetVariateSrollUp(const QString& scope, const QString& name)
	//  Description:   根据当前作用域及变量名查找当前及以上所有作用域内的变量，若未找到则返回nullptr
	//  Author:        刘巍 
	//  Date:          2016/11/16
	//  Returns:       TVariate* :查找到的变量指针，若未找到，为nullptr
	//  Parameter:     const QString& scope:开始查找的起始作用域
	//		const QString& name:变量名
	//  History:
	*************************************************/
	std::shared_ptr<TVariate> GetVariateSrollUp(const QString& scope, const QString& name);

	void LoadInitDataFromDatabase();

	//void UpdateVariate(const QString& scope, const QString& name, std::shared_ptr<TVariate> newVariate);
	void UpdateVariate(std::shared_ptr<TVariate> newVariate);
	void UpdateInMapScollUp(std::shared_ptr<TVariate> newVariate);


private:
	void AddInDatabase(std::shared_ptr<TVariate> variate);
	void UpdateInDatabase(const QString& scope, const QString& name, std::shared_ptr<TVariate> variate);

private:
	VariateMAP m_objectMap;
	std::unique_ptr<TScope> m_scopeRoot;
};

#endif