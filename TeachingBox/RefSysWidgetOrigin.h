#ifndef _TEACHING_BOX_REF_SYS_WIDGET_ORIGIN_H_
#define _TEACHING_BOX_REF_SYS_WIDGET_ORIGIN_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    RefSysWidgetOrigin.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/18
//  Description:    参考坐标系示教初始化界面
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/18
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "SystemDialogWidgetParent.h"

class RefSysWidgetOrigin:public SystemDialogWidgetParent
{
public:
	enum TeachMethod
	{
		THREE_POINTS_WITH_ORIGIN,
		THREE_POINTS_WITHOUT_ORIGIN,
		ONE_POINT_KEEP_ORIENTATION,
	};

public:
	RefSysWidgetOrigin(SystemDialogWidgetParent* threePointsWithOrigin, SystemDialogWidgetParent* threePointsWithoutOrigin,
		SystemDialogWidgetParent* onePointKeepOrientation, QStackedWidget* parent = nullptr);

	virtual QWidget* MainWidget() override;
	virtual QString IllustrationPixmapPath() override;
	virtual void OnReseivePose(const tPoseEuler& pose/* = */)override;

private:
	virtual void showEvent(QShowEvent *event) override;

	QWidget* GetTeachMethodWidget();
	QWidget* GetTeachToolWidget();

	void InitCoorInfo();

private:
	SystemDialogWidgetParent* m_threePointsWithOrigin;
	SystemDialogWidgetParent* m_threePointsWithoutOrigin;
	SystemDialogWidgetParent* m_onePointKeepOrientation;
};

#endif