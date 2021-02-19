#ifndef _TEACHING_BOX_DIALOG_NEW_ROBOT_H_
#define _TEACHING_BOX_DIALOG_NEW_ROBOT_H_

/*************************************************
//  Copyright (C), 2020-2021, CS&S. Co., Ltd.
//  File name: 	    DialogNewRobot.h
//  Author:			��Ρ
//  Version: 		1.0
//  Date: 			2021/02/19
//  Description:	��������»�������Ϣ
//  Others:
//  History:
//    <author>      ��Ρ
//    <time>        2021/02/19
//    <version>     1.0
//    <desc>        build this moudle
*************************************************/

#include "QLineEdit"
#include "QDialog"
#include "QSpinBox"

class Button;

class DialogNewRobot :public QDialog
{
	Q_OBJECT

public:
	DialogNewRobot(QWidget* parent);

private:
	void initWidget();
	void initSignalSlot();

private:
	QLineEdit* nameLineEdit;
	QSpinBox* idSpinBox;
	Button* confirmButton;
	Button* cancelButton;
};

#endif