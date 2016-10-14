#ifndef _TEACHING_BOX_T_VARIATE_WIDGET_H_
#define _TEACHING_BOX_T_VARIATE_WIDGET_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TVariateWidget.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/10/12
//  Description:	用于生成变量的编辑控件，作为各种变量的父类
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/10/12
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QObject"

class TVariate;
class QTreeWidgetItem;
class QTreeWidget;
class TreeWidgetItemWithVariate;

class TVariateWidget:public QObject
{
	Q_OBJECT

public:
	TVariateWidget(TVariate* variate);
	virtual ~TVariateWidget();
	
	virtual void UpdateVariate()=0;

	void ReadTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget);

	void ReadContentIntoItem(TreeWidgetItemWithVariate* parentItem, QTreeWidget* treeWidget);


protected slots:
	void SlotOnValueChanged();

protected:
	virtual void OnValueChanged()=0;

private:
	virtual void ReadContentTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget) = 0;

protected:
	TVariate* m_variate;
	TreeWidgetItemWithVariate* m_itemVariateHeader = nullptr;
};

#endif