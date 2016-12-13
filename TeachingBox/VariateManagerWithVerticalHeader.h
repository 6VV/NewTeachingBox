#ifndef _TEACHING_BOX_VARIATE_MANAGER_WITH_VERTICAL_HEADER_H_
#define _TEACHING_BOX_VARIATE_MANAGER_WITH_VERTICAL_HEADER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    VariateManagerWithVerticalHeader.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/12/12
//  Description:    用于管理各种变量的树形控件，包括生成控件，从控件获取变量，更新控件等,
		本类生成的变量控件头部采用竖直方向显示变量信息
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/12/12
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <memory>

class TVariate;
class QTreeWidget;
class QTreeWidgetItem;

class VariateManagerWithVerticalHeader
{
public:
	static VariateManagerWithVerticalHeader* GetInstance();

	/*************************************************
	//  Method:        static void InsertVariate(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* parentItem)
	//  Description:   将变量插入到树形控件中
	//  Author:        刘巍
	//  Date:          2016/11/29
	//  Returns:       void
	//  Parameter:     const std::shared_ptr<TVariate> variate:将要插入的变量
	QTreeWidget* treeWidget：被插入的树形控件
	QTreeWidgetItem* parentItem：被插入的树形控件项
	//  History:
	*************************************************/
	void InsertVariate(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* parentItem);

	/*************************************************
	//  Method:        static std::shared_ptr<TVariate> GetVariate(QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
	//  Description:   从树形控件中获取变量
	//  Author:        刘巍
	//  Date:          2016/12/12
	//  Returns:       std::shared_ptr<TVariate>：获取的变量，该变量为新建变量。
	//  Parameter:     QTreeWidget* treeWidget：树形控件
			QTreeWidgetItem* variateItem：变量项
	//  History:
	*************************************************/
	std::shared_ptr<TVariate> GetVariate(QTreeWidget* treeWidget, QTreeWidgetItem* variateItem);

	/*************************************************
	//  Method:        static void UpdateWidget(const std::shared_ptr<TVariate> newVariate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
	//  Description:   根据变量更新树形控件
	//  Author:        刘巍
	//  Date:          2016/12/12
	//  Returns:       const std::shared_ptr<TVariate> newVariate:新变量
			QTreeWidget* treeWidget：树形控件
			QTreeWidgetItem* variateItem：变量项
	//  Parameter:
	//  History:
	*************************************************/
	void UpdateWidget(const std::shared_ptr<TVariate> newVariate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem);
};

#endif