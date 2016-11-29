#ifndef _TEACHING_BOX_TVARIATE_H_
#define _TEACHING_BOX_TVARIATE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TVariate.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/14
//  Description:	所有变量的父类
	提供了变量需具有的基本信息，包括变量名、作用域、变量类型
	提供变量需具有的基本功能，包括：
		Clone：新建并返回一个与本变量相同的变量；
		UpdateFromVariate：从另一个同类型的变量中复制值；
		Save：保存值并更新显示控件；
		ReadTreeWidgetItem：将变量添加到树形控件中
		ReadContentIntoItem：根据变量更新控件显示数据
		WriteToCollection：将变量添加到集合中
		ReadDataStream：从数据流中更新变量
	需子类实现的功能：
		virtual TVariate* Clone() const=0
		virtual void WriteValueToStream(QDataStream& dataStream) const=0;
		virtual void UpdateFromValue(const TVariate& variate) =0;

//  Others:	m_variateWidget需有子类重新赋值，才能生成正确的显示控件
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/14
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "TSymbol.h"

class TVariateWidget;
class TreeWidgetItemWithVariate;
class QTreeWidgetItem;
class QTreeWidget;

class TVariate:public QObject
{
	Q_OBJECT

public:
	TVariate(const TSymbol& symbol);
	TVariate(const TVariate& variate);
	TVariate(QDataStream& dataStream);
	virtual ~TVariate();

public:
	virtual TVariate* Clone() const = 0;

	TSymbol GetSymbol() const;
	QString GetScope() const;
	QString GetName() const;
	TSymbol::SymbolType GetType() const;	/*获取变量类型*/
	QString GetTypeName() const;	/*获取变量类型名*/

	void Save();

	void WriteContentIntoItem(TreeWidgetItemWithVariate* parentItem, QTreeWidget* treeWidget);	/*利用值更新控件内容*/

	void WriteToTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget);	/*将变量添加到控件中*/
	void WriteToTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget,	
		const TSymbol::SymbolType type);/*当变量类型与需求类型相同时，将变量添加到控件中*/

	void WriteDataToStream(QDataStream& dataStream) const;	/*将变量读入到数据流中*/
	//void WriteToCollection(SET& collection, const TSymbol::SymbolType type);	/*当变量类型与需求类型相同时，将变量添加到集合中*/

	void UpdateFromVariate(const TVariate& variate);	/*更新变量值*/

protected:
	virtual void WriteValueToStream(QDataStream& dataStream) const=0;
	virtual void UpdateFromValue(const TVariate& variate) =0;

private:
	void UpdateRamAndDatabaseFrom(const TVariate& variate) const;

protected:
	TSymbol m_symbol;
	TVariateWidget* m_variateWidget=nullptr;
};

#endif