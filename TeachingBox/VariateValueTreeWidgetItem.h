#ifndef _TEACHING_BOX_VARIATE_VALUE_TREE_WIDGET_ITEM_H_
#define _TEACHING_BOX_VARIATE_VALUE_TREE_WIDGET_ITEM_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    VariateTreeWidget.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/29
//  Description:    提供树形控件列表项，用于显示变量值，本类为虚类，提供变量控件的相关操作，包括根据变量生成控件，从控件中获取变量，根据变量更新控件等
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/11/29
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <memory>
#include "QObject"

class TVariate;
class QTreeWidget;
class QTreeWidgetItem;
class TSymbol;

class VariateValueTreeWidgetItem:public QObject
{
	Q_OBJECT

signals:
	void SignalValueChanged();

public:
	virtual ~VariateValueTreeWidgetItem();

	virtual std::shared_ptr<TVariate> GetVariate(const TSymbol& symbol, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)=0;
	virtual void UpdateWidgetValue(const std::shared_ptr<TVariate> newVariate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)=0;

	void InsertVariate(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem);

protected:
	virtual void InsertVariateValue(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem) = 0;

	void InsertInt(const QString& valueName, int value, QTreeWidget* treeWidget, QTreeWidgetItem* parentItem);
	void InsertDouble(const QString& valueName, double value, QTreeWidget* treeWidget, QTreeWidgetItem* parentItem);
	void InsertLineEdit(const QString& valueName, const QString& value, const QString& regExp, QTreeWidget* treeWidget, QTreeWidgetItem* parentItem);

	int GetInt(QTreeWidget* treeWidget, QTreeWidgetItem* valueItem);
	double GetDouble(QTreeWidget* treeWidget, QTreeWidgetItem* valueItem);

};

#endif