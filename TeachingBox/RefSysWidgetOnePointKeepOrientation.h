#ifndef _TEACHING_BOX_REF_SYS_WIDGET_ONE_POINT_KEEP_ORIENTATION_H_
#define _TEACHING_BOX_REF_SYS_WIDGET_ONE_POINT_KEEP_ORIENTATION_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    RefSysWidgetOnePointKeepOrientation.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/18
//  Description:    一点（保持原点）坐标系示教法步骤1
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/18
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "SystemDialogWidgetParent.h"

class RefSysWidgetOnePointKeepOrientation :public SystemDialogWidgetParent
{
	Q_OBJECT
public:
	RefSysWidgetOnePointKeepOrientation(QStackedWidget* parent);

private:
	virtual QWidget* MainWidget() override;

	virtual QString IllustrationPixmapPath() override;

	virtual void OnReseivePose(const tPoseEuler& pose/* = */) override;
};

#endif