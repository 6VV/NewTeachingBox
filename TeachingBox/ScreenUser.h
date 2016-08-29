#ifndef _TEACHING_BOX_SCREEN_USER_H_
#define _TEACHING_BOX_SCREEN_USER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenUser.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/07/29
//  Description:	用于显示当前用户信息
//  Others:
//  History:
//    <author>      刘巍 
//    <time>        2016/07/29
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "InternationalWidget.h"

class QTableWidget;

class ScreenUser:public InternationalWidget
{
public:
	ScreenUser(QWidget* parent);
	~ScreenUser();

private:
	void showEvent(QShowEvent *) override;
	virtual void UpdateText() override;

	void Init();

private:
	const char* CLASS_NAME = "ScreenUser";
	QTableWidget* m_tableWidget;;
};

#endif