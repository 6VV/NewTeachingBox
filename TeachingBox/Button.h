#ifndef _BUTTON_H_
#define _BUTTON_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    Button.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/07/27
//  Description:	自定义按钮，用于统一定制示教盒中按钮样式
//  Others:
//  History:
//    <author>      刘巍 
//    <time>        2016/07/27
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QPushButton"

class Button:public QPushButton
{
public:
	Button(const QString& text, QWidget* parent = 0);
	Button(QWidget* parent = 0);

private:
	void Init();
};

#endif