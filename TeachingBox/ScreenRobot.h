#ifndef _TEACHING_BOX_SCREEN_ROBOT_H_
#define _TEACHING_BOX_SCREEN_ROBOT_H_

/*************************************************
//  Copyright (C), 2020-2021, CS&S. Co., Ltd.
//  File name: 	    ScreenRobot.h
//  Author:			刘巍
//  Version: 		1.0
//  Date: 			2021/02/19
//  Description:	用于设置机器人信息
//  Others:
//  History:
//    <author>      刘巍
//    <time>        2021/02/19
//    <version>     1.0
//    <desc>        build this moudle
*************************************************/

#include "QTableWidget"
#include "InternationalWidget.h"

class Button;

class ScreenRobot :public InternationalWidget
{
	Q_OBJECT

public:
	ScreenRobot(QWidget* parent = nullptr);

private:
	virtual void UpdateText() override;

	void initWidget();
	void initSignalSlot();

	void updateTable();

private:
	QTableWidget* tableWidget = nullptr;
	Button* addButton = nullptr;
	Button* deleteButton = nullptr;
};

#endif