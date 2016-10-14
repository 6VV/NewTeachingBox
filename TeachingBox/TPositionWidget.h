#ifndef _TEACHING_BOX_T_POSITION_WIDGET_H_
#define _TEACHING_BOX_T_POSITION_WIDGET_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TPositionWidget.h
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

class TPosition;

class TPositionWidget:public TVariateWidget
{
	Q_OBJECT

public:
	TPositionWidget(TPosition* positon);
	~TPositionWidget();

	virtual void UpdateVariate() override;

	tAxesAllPositions Value() const;

private:
	virtual void ReadContentTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget) override;

private:
	virtual void OnValueChanged() override;


private:
	tAxesAllPositions m_value;
};

#endif