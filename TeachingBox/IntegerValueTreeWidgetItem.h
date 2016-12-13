#ifndef _TEACHING_BOX_INTEGER_VALUE_TREE_WIDGET_ITEM_H_
#define _TEACHING_BOX_INTEGER_VALUE_TREE_WIDGET_ITEM_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    IntegerValueTreeWidgetItem.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/29
//  Description:    提供整型变量值的树形控件的相关操作
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

class IntegerValueTreeWidgetItem :public VariateValueTreeWidgetItem
{
public:

	virtual std::shared_ptr<TVariate> GetVariate(const TSymbol& symbol, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem,int index=0) override;

	virtual void InsertVariateValue(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem) override;

	virtual void UpdateWidgetValue(const std::shared_ptr<TVariate> newVariate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem) override;

private:
	static VariateValueTreeWidgetBuilder<IntegerValueTreeWidgetItem> builder;
};

#endif