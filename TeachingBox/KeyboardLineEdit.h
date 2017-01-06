#ifndef _TEACHING_BOX_KEYBOARD_LINE_EDIT_H_
#define _TEACHING_BOX_KEYBOARD_LINE_EDIT_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    KeyboardLineEdit.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/05
//  Description:    能够响应键盘按钮事件的行编辑器
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/05
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "IKeyboard.h"
#include "QLineEdit"

class KeyboardLineEidt:public QLineEdit,public IKeyboard
{
public:
	KeyboardLineEidt(QWidget* parent=nullptr);
	~KeyboardLineEidt()=default;

	virtual void OnInsert(const QString& text) override;

private:
};

#endif