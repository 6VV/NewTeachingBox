#ifndef _TEACHING_BOX_T_OVERLAP_WIDGET_H_
#define _TEACHING_BOX_T_OVERLAP_WIDGET_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TOverlapWidget.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/10/12
//  Description:	用于生成TOverlap的编辑控件
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

class TOverlap;

class TOverlapWidget:public TVariateWidget
{
	Q_OBJECT

private:
	static const QString STR_MODE_ABSOLUTE;
	static const QString STR_MODE_RELATIVE;

public:
	TOverlapWidget(TOverlap* overlap);
	~TOverlapWidget();

	virtual void UpdateVariate() override;

	tOverlapConstraint Value() const;

private:
	virtual void WriteContentToTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget) override;

private:
	virtual void OnValueChanged() override;

private:
	tOverlapConstraint m_value;
};

#endif