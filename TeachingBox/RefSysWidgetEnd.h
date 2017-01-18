#ifndef _TEACHING_BOX_REF_SYS_WIDGET_END_H_
#define _TEACHING_BOX_REF_SYS_WIDGET_END_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    RefSysWidgetEnd.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/18
//  Description:    参考坐标系示教结束界面
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/18
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "SystemDialogWidgetParent.h"

class RefSysWidgetEnd:public SystemDialogWidgetParent
{
public:
	RefSysWidgetEnd(QStackedWidget* parent = nullptr);

	virtual QWidget* MainWidget() override;

	virtual QString IllustrationPixmapPath() override;

	virtual void OnReseivePose(const tPoseEuler& pose/* = */) override;

	virtual bool HaveNext() override;

private:
	virtual void OnNextButtonClicked() override;
};

#endif