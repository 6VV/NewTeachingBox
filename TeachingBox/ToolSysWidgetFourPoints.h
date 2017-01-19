#ifndef _TEACHING_BOX_TOOL_SYS_WIDGET_FOUR_POINTS_H_
#define _TEACHING_BOX_TOOL_SYS_WIDGET_FOUR_POINTS_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ToolSysWIdgetFourPoints.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/19
//  Description:    四点法工具坐标系示教
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/19
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "SystemDialogWidgetParent.h"


class ToolSysWidgetFourPoints:public SystemDialogWidgetParent
{
public:
	ToolSysWidgetFourPoints(QStackedWidget* parent,const QString& pixmapPath="",const QString& title="");
	~ToolSysWidgetFourPoints()=default;

private:
	virtual QWidget* MainWidget() override;
	virtual QString IllustrationPixmapPath() override;

	virtual void OnReseivePose(const tPoseEuler& pose/* = */) override;

private:
	QString m_title="";
	QString m_pixmapPath="";
};

#endif