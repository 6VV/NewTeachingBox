#ifndef _TEACHING_BOX_SCREEN_H_
#define _TEACHING_BOX_SCREEN_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    Screen.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/07/27
//  Description:	屏幕部分，包括顶部状态栏、警告信息栏、轴、主界面
//  Others:
//  History:
//    <author>      刘巍 
//    <time>        2016/07/27
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QWidget"
class QLayout;

class Screen:public QWidget
{
private:
	const int HEAD_HEIGHT_RATIO = 2;
	const int WARNING_HEIGHT_RATIO = 1;
	const int MAIN_SCREEN_HEIGHT_RATIO = 13;

	const int LEFT_WIDTH_RATIO = 8;
	const int RIGHT_WIDTH_RATIO = 1;

public:
	Screen(QWidget* parent=0);
	~Screen();

protected:
	void showEvent(QShowEvent *e) override;

private:
	void Init();
	QLayout* GetBottomLayout();
	QLayout* GetLeftLayout();
};

#endif