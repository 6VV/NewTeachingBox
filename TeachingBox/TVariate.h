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
	virtual ~TVariate();

public:
	virtual TVariate* Clone() const = 0;
	virtual void WriteValueToStream(QDataStream& dataStream) const = 0;	/*将变量值读入到数据流*/
	virtual void ReadValueFromStream(QDataStream& dataStream) = 0;

	TSymbol GetSymbol() const;
	QString GetScope() const;
	QString GetName() const;
	TSymbol::SymbolType GetType() const;	/*获取变量类型*/
	QString GetTypeName() const;	/*获取变量类型名*/

	void SetSymbol(const TSymbol& symbol);
	void SetName(const QString& name);
	void SetScope(const QString& scope);

	void ReadDataFromStream(QDataStream& dataStream);
	void WriteDataToStream(QDataStream& dataStream) const;	/*将变量读入到数据流中*/

protected:
	TVariate(const TVariate& variate);

private:
	void UpdateRamAndDatabaseFrom(const TVariate& variate) const;

protected:
	TSymbol m_symbol;
};

#endif