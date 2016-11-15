#ifndef _TEACHING_BOX_SCREEN_TEACH_REFERENCE_SYSTEM_H_
#define _TEACHING_BOX_SCREEN_TEACH_REFERENCE_SYSTEM_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenTeachReferenceSystem.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/14
//  Description:	用于生成参考坐标系示教界面，该界面以对话框的形式出现。
	共包括三种示教方法：1、3点（含原点）示教法；2、三点（无原点）示教法；3、一点（保持姿态）示教法。
	对于每种方法的每一步骤，都提供指导界面及示意图进行操作。
	可在任意步骤下停止操作。

//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/14
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "InternationalWidget.h"

class ScreenTeachReferenceSystem:InternationalWidget
{
public:
	ScreenTeachReferenceSystem(QWidget* parent=nullptr);

	virtual void UpdateText() override;

private:
	QWidget* GetReferenceSystemWidget();
	QLayout* GetTeachLayout();
	QWidget* GetTeachMethodWidget();
	QWidget* GetTeachToolWidget();
	QWidget* GetIllustrationWidget();

	void Init();
};

#endif