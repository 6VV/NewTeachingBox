#ifndef _SCREEN_WARNING_H_
#define _SCREEN_WARNING_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenWarning.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/07/28
//  Description:	用于监听并显示当前警告信息
//  Others:			只有在所有警告信息都被清除的情况下，才能继续控制机器人运行
//  History:
//    <author>      刘巍 
//    <time>        2016/07/28
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "InternationalWidget.h"

class LabelWithBorder;
class Button;

class ScreenWarning:public InternationalWidget
{
	Q_OBJECT

public:
	ScreenWarning(QWidget* parent=0);
	~ScreenWarning();

private:
	virtual void UpdateText() override;

	void Init();

private:
	LabelWithBorder* m_labelWarning;
	Button* m_btnConfrim;

};

#endif