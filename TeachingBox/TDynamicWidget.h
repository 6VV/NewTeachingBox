#ifndef _TEACHING_BOX_T_DYNAMIC_WIDGET_H_
#define _TEACHING_BOX_T_DYNAMIC_WIDGET_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TDynamicWidget.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/10/12
//  Description:	用于生成TPosition的编辑控件
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/10/12
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "TVariateWidget.h"
#include "DataStruct.h"

class TDynamic;

class TDynamicWidget:public TVariateWidget
{
	Q_OBJECT

public:
	TDynamicWidget(TDynamic* dynamic);
	~TDynamicWidget();

	virtual void UpdateVariate() override;

private:
	virtual void ReadContentTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget) override;

private:
	virtual void OnValueChanged() override;

private:
	tDynamicConstraint m_value;
};

#endif