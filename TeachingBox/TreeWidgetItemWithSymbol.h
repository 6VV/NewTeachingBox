#ifndef _TEACHING_BOX_TREE_WIDGET_ITEM_WITH_SYMBOL_H_
#define _TEACHING_BOX_TREE_WIDGET_ITEM_WITH_SYMBOL_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TreeWidgetItemWithSymbol.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/29
//  Description:    QTreeWidgetItem的子类，该类对象用于显示变量数据，并维护一个TSymbol对象
		该类与VariateTreeWidget配合使用，用于设置、获取变量信息
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/11/29
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "TSymbol.h"
#include "QTreeWidget"
#include "QObject"

class TreeWidgetItemWithSymbol :public QObject,public QTreeWidgetItem
{
	Q_OBJECT

public:
	TreeWidgetItemWithSymbol(const TSymbol& symbol, QTreeWidgetItem* parentItem);
	~TreeWidgetItemWithSymbol();

	TSymbol GetSymbol() const;
	bool IsSave() const;

	void SetSymbol(const TSymbol& symbol);
	void SetSave(bool isSave);

private:
	TSymbol m_symbol;
	bool m_isSave=false;
};

#endif