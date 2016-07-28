#ifndef _TEACHING_BOX_H_
#define _TEACHING_BOX_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    teachingbox.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/07/26
//  Description:	该类用于定义示教盒面板，包括外部物理按钮、显示屏等
//  Others:			该类只能生成唯一实例
//  History:
//    <author>      刘巍 
//    <time>        2016/07/26
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "InternationalWidget.h"

class WarningLight;
class QButtonGroup;

class TeachingBox : public InternationalWidget
{
	Q_OBJECT

private:
	const int HEIGHT_RATIO = 24;	/*示教盒高度所占比例*/
	const int CENTER_HEIGHT_RATIO = 20;	/*中间部分高度所占比例*/
	const int TOP_HEIGHT_RATIO = 2;		/*顶部高度所占比例*/
	const int BOTTOM_HEIGHT_RATIO = 2;	/*底部高度所占比例*/

	const int WIDTH_RATIO = 28;		/*示教盒宽度所占比例*/
	const int SCREEN_WIDTH_RATIO = 20;	/*屏幕宽度所占比例*/
	const int WARNING_WIDTH_RATIO = 2;	/*警告部分宽度所占比例*/
	const int OPTION_WIDTH_RATIO = 2;	/*选项部分宽度所占比例*/
	const int MOVEMENT_WIDTH_RATIO = 4;	/*机器人控制部分宽度所占比例*/

	const int SCREEN_WIDTH = 800;	/*屏幕宽度*/
	const int SCREEN_HEIGHT = 600;	/*屏幕高度*/
	const int WIDTH = SCREEN_WIDTH*WIDTH_RATIO / SCREEN_WIDTH_RATIO;		/*示教盒总高度*/
	const int HEIGHT = SCREEN_HEIGHT*HEIGHT_RATIO / CENTER_HEIGHT_RATIO;		/*示教盒总宽度*/

public:
	TeachingBox(QWidget *parent = 0);
	~TeachingBox();

private:
	void Init();
	void InitBottom(QLayout* layout);
	void InitCenter(QLayout* layout);
	void InitOption(QLayout* layout);
	void InitMovement(QLayout* layout);
	void InitScreen(QLayout* layout);
	void InitTop(QLayout* layout);
	void InitVertical();
	void InitWarning(QLayout* layout);

private slots:
	void SlotOnModelChanged();

	virtual void UpdateText() override;

private:
	QButtonGroup* m_modelButtonGroup;

	WarningLight* m_clRun;
	WarningLight* m_clError;
	WarningLight* m_clPro;
	WarningLight* m_clMot;
};

#endif // TEACHINGBOX_H
