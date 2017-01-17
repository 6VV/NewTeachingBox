#ifndef _TEACHING_BOX_CONFIRM_BUTTON_H_
#define _TEACHING_BOX_CONFIRM_BUTTON_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ConfirmButton.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/16
//  Description:    确认按钮，显示确认图标
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/16
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "Button.h"

class ConfirmButton :public Button
{
	Q_OBJECT

public:
	ConfirmButton(QWidget* parent = nullptr);
};

#endif