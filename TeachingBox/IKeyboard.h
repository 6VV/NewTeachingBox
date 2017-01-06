#ifndef _TEACHING_BOX_I_KEYBOARD_H_
#define _TEACHING_BOX_I_KEYBOARD_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    IKeyboard.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/05
//  Description:    提供键盘操作的接口，响应键盘按钮事件
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/05
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

class IKeyboard
{
public:
	virtual ~IKeyboard(){};

	virtual void OnInsert(const QString& text) = 0;	/*插入字符串*/
};

#endif