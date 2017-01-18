#ifndef _TEACHING_BOX_REF_SYS_WIDGET_THREE_POINTS_WITHOUT_ORIGIN_STEP_3_H_
#define _TEACHING_BOX_REF_SYS_WIDGET_THREE_POINTS_WITHOUT_ORIGIN_STEP_3_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    RefSysWidgetThreePointsWithoutOriginStep3.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/18
//  Description:    三点（不含原点）坐标系示教法步骤3
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/18
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "SystemDialogWidgetParent.h"

class RefSysWidgetThreePointsWithoutOriginStep3:public SystemDialogWidgetParent
{
public:
	RefSysWidgetThreePointsWithoutOriginStep3(QStackedWidget* parent);

private:
	virtual QWidget* MainWidget() override;

	virtual QString IllustrationPixmapPath() override;

	virtual void OnReseivePose(const tPoseEuler& pose/* = */) override;

private:
	QButtonGroup* m_btnGroup;
};

#endif