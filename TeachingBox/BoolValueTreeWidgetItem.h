#ifndef _TEACHING_BOX_BOOL_VALUE_TREE_WIDGET_ITEM_H_
#define _TEACHING_BOX_BOOL_VALUE_TREE_WIDGET_ITEM_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    BoolValueTreeWidgetItem.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/29
//  Description:    提供布尔型树形控件相关操作，包括生成控件，从控件中获取变量，继承自VariateValueTreeWidgetItem
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/11/29
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "VariateValueTreeWidgetItem.h"
#include "VariateValueTreeWidgetBuilder.h"

class BoolValueTreeWidgetItem :public VariateValueTreeWidgetItem
{
private:
	static const QString TRUE_VALUE;
	static const QString FALSE_VALUE; 

public:
	virtual std::shared_ptr<TVariate> GetVariate(const TSymbol& symbol, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem) override;

	virtual void InsertVariateValue(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem) override;

	virtual void UpdateWidgetValue(const std::shared_ptr<TVariate> newVariate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem) override;

private:
	static VariateValueTreeWidgetBuilder<BoolValueTreeWidgetItem> builder;
};

#endif