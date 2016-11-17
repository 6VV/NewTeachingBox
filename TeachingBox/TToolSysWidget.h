#ifndef _TEACHING_BOX_T_TOOL_SYS_WIDGET_H_
#define _TEACHING_BOX_T_TOOL_SYS_WIDGET_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TToolSysWidget.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/16
//  Description:	用于提供工具坐标系变量控件的相关操作
	继承自TVariateWidget类
	提供额外功能：
	获取变量值
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/16
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "TVariateWidget.h"
#include "TToolSys.h"

class TToolSysWidget:public TVariateWidget
{
public:
	TToolSysWidget(TVariate* variate);
	~TToolSysWidget();

	virtual void UpdateVariate() override;

private:
	virtual void OnValueChanged() override;
	virtual void WriteContentToTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget) override;

private:
	TToolSys::ValueType m_value;
};

#endif