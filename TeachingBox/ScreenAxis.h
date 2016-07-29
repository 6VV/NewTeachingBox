#ifndef _TEACHING_BOX_SCREEN_AXIS_H_
#define _TEACHING_BOX_SCREEN_AXIS_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenAxis.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/07/28
//  Description:	用于显示当前采用何种坐标系
//  Others:
//  History:
//    <author>      刘巍 
//    <time>        2016/07/28
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <QWidget>

class LabelWithBorder;

class ScreenAxis:public QWidget
{
public:
	ScreenAxis(QWidget* parent=0);
	
private:
	void Init();

private:
	LabelWithBorder* m_axis1;
	LabelWithBorder* m_axis2;
	LabelWithBorder* m_axis3;
	LabelWithBorder* m_axis4;
	LabelWithBorder* m_axis5;
	LabelWithBorder* m_axis6;

};

#endif // !_SCREEN_AXIS_H_
