#ifndef _TEACHING_BOX_VARIATE_VALUE_H_
#define _TEACHING_BOX_VARIATE_VALUE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    VariateValue.h
//  Author:			刘巍
//  Version: 		1.0
//  Date: 			2016/12/13
//  Description:    变量值接口，提供变量值的相关操作
//  Others:
//  Function List:
//  History:
//    <author>      刘巍
//    <time>        2016/12/13
//    <version>     1.0
//    <desc>        build this moudle
*************************************************/

#include "QObject"

class QDataStream;
class QTreeWidget;
class QTreeWidgetItem;

class VariateValue
{
public:
	virtual ~VariateValue();

	/*************************************************
	//  Method:        void WriteToDataStream(QDataStream& dataStream)
	//  Description:   将变量值写入到字节流
	//  Author:        刘巍
	//  Date:          2016/12/14
	//  Returns:       void
	//  Parameter:     QDataStream& dataStream：被写入的字节流
	//  History:
	*************************************************/
	virtual void WriteToDataStream(QDataStream& dataStream) const = 0;

	///*************************************************
	////  Method:        void WriteToTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column)
	////  Description:   将变量值写入到树形控件中，本操作不会新增节点，必须保证树形控件相关节点已经创建
	////  Author:        刘巍
	////  Date:          2016/12/14
	////  Returns:       void
	////  Parameter:     QTreeWidget* treeWidget：树形控件；
	//QTreeWidgetItem* parentItem：变量值所在的父节点；
	//int row：写入的开始行数；
	//int column：写入的对应列数
	////  History:
	//*************************************************/
	//virtual void WriteToTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column) const = 0;

	//virtual void UpdateTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column) const = 0;

	/*************************************************
	//  Method:        void ReadFromDataStream(QDataStream& dataStream)
	//  Description:   从字节流读出数据
	//  Author:        刘巍
	//  Date:          2016/12/14
	//  Returns:       void
	//  Parameter:     QDataStream& dataStream：读取的字节流
	//  History:
	*************************************************/
	virtual void ReadFromDataStream(QDataStream& dataStream) = 0;

	///*************************************************
	////  Method:        void ReadFromTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column)
	////  Description:   从树形控件中读出数据
	////  Author:        刘巍
	////  Date:          2016/12/14
	////  Returns:       void
	////  Parameter:     QTreeWidget* treeWidget：树形控件；
	//QTreeWidgetItem* parentItem：读取的数据所在的父节点；
	//int row：开始读取的行数；
	//int column：读取的列数；
	////  History:
	//*************************************************/
	//virtual void ReadFromTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column) = 0;
};

#endif