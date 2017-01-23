#ifndef _TEACHING_BOX_DIALOG_LOCK_SCREEN_H_
#define _TEACHING_BOX_DIALOG_LOCK_SCREEN_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    DialogLockScreen.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/20
//  Description:    对话框，用于锁定屏幕，此时用户不可通过点击屏幕进行操作，可用于清理屏幕灰尘等操作
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/20
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "DialogParent.h"

class DialogLockScreen:public DialogParent
{
	Q_OBJECT

signals:
	void SignalStopTimer();

public:
	DialogLockScreen(QWidget* parent=nullptr,int lockTime=16);
	~DialogLockScreen();

	virtual void SetSize() override;

	virtual void UpdateText() override;

private:
	int m_lockTime=0;
	QThread* m_thread;
};

#endif