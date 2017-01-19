#ifndef _TEACHING_BOX_TOOL_SYS_WIDGET_ORIGIN_H_
#define _TEACHING_BOX_TOOL_SYS_WIDGET_ORIGIN_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ToolSysWidgetOrigin.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/19
//  Description:    工具坐标系示教选择界面
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/19
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "SystemDialogWidgetParent.h"

class ToolSysWidgetOrigin:public SystemDialogWidgetParent
{
public:
	ToolSysWidgetOrigin(QStackedWidget* parent = nullptr);
	~ToolSysWidgetOrigin()=default;

private:
	virtual void showEvent(QShowEvent *event) override;
	virtual QWidget* MainWidget() override;
	virtual QString IllustrationPixmapPath() override;

	void InitCoorState();
};

#endif