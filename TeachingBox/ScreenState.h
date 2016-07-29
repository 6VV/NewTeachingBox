#ifndef _TEACHING_BOX_SCREEN_HEAD_H_
#define _TEACHING_BOX_SCREEN_HEAD_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenState.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/07/27
//  Description:	屏幕中状态栏部分，实时显示机器人当前状态
//  Others:
//  History:
//    <author>      刘巍 
//    <time>        2016/07/27
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "InternationalWidget.h"
#include "QLabel"

class QLayout;
class LabelWithBorder;

class ScreenState:public InternationalWidget
{
public:
	ScreenState(QWidget* parent=0);
	~ScreenState();

private:
	virtual void UpdateText() override;

	void Init();
	void InitLayout();
	QLayout* GetFirstLayout();
	QLayout* GetSecondLayout();

private:
	LabelWithBorder* m_lbOperationMode;	/*操作模式*/
	LabelWithBorder* m_lbServo;			/*机器人状态*/
	LabelWithBorder* m_lbCoordinate;		/*参考坐标系*/
	LabelWithBorder* m_lbTool;			/*工具手*/
	LabelWithBorder* m_lbSpeedPersent;	/*机器人速度*/
	LabelWithBorder* m_lbLogo;			/*商标*/

	LabelWithBorder* m_lbProjectAndProgram;		/*项目与程序*/
	LabelWithBorder* m_lbProgramState;			/*程序状态*/
	LabelWithBorder* m_lbProgramRunningMode;		/*同上*/
	LabelWithBorder* m_lb3;				/*用户自定义*/
	LabelWithBorder* m_lb4;				/*同上*/
	LabelWithBorder* m_lb5;				/*同上*/
	LabelWithBorder* m_lbSpace;			/*空间监控*/
	LabelWithBorder* m_lbSecurityState;	/*安全状态*/
	LabelWithBorder* m_lbUserAuthority;	/*用户权限*/
	LabelWithBorder* m_lbCurrentTime;	/*当前时间*/
};

#endif