#ifndef _TEACHING_BOX_KEYBOARD_BUTTON_H_
#define _TEACHING_BOX_KEYBOARD_BUTTON_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    CButtonKeyBoard.h
//  Author:			��Ρ      
//  Version: 		1.0     
//  Date: 			2016/08/29
//  Description:	�Զ�����̰���
//  Others:
//  Function List:
//  History:
//    <author>      ��Ρ 
//    <time>        2016/08/29
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QToolButton"

class KeyboardButton:public QToolButton
{
public:
	KeyboardButton(QWidget* parent=0);
	KeyboardButton(const QString& text, QWidget* parent = 0);
	~KeyboardButton();

private:
	void Init();
};


#endif