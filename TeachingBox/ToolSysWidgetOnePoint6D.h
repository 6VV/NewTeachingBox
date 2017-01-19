#ifndef _TEACHING_BOX_TOOL_SYS_WIDGET_ONE_POINT_6_D_H_
#define _TEACHING_BOX_TOOL_SYS_WIDGET_ONE_POINT_6_D_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ToolSysWidgetOnePoint6D.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/19
//  Description:    工具坐标系示教1点6D法
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/19
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "SystemDialogWidgetParent.h"

class QLayout;

class ToolSysWidgetOnePoint6D:public SystemDialogWidgetParent
{
public:
	ToolSysWidgetOnePoint6D(QStackedWidget* parent);

private:
	virtual QWidget* MainWidget() override;
	virtual QString IllustrationPixmapPath() override;
	virtual void OnReseivePose(const tPoseEuler& pose = {}) override;

	QLayout* DirectionLayout();

	void UpdateCoorDirection();

private:
	QCheckBox* m_invertBox;
	QComboBox* m_axisBox;
};

#endif