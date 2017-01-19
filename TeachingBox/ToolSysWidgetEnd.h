#ifndef _TEACHING_BOX_TOOL_SYS_WIDGET_END_H_
#define _TEACHING_BOX_TOOL_SYS_WIDGET_END_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ToolSysWidgetEnd.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/19
//  Description:    工具坐标系示教结束
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/19
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "SystemDialogWidgetParent.h"

class ToolSysWidgetEnd:public SystemDialogWidgetParent
{
public:
	ToolSysWidgetEnd(QStackedWidget* parent);

private:
	virtual bool HaveNext() override;
	virtual QString IllustrationPixmapPath() override;
	virtual QWidget* MainWidget() override;

	virtual void OnReseivePose(const tPoseEuler& pose/* = */) override;
	virtual void OnNextButtonClicked() override;

	virtual void showEvent(QShowEvent *event) override;

private:
	tPoseEuler m_poseEuler{};
};

#endif