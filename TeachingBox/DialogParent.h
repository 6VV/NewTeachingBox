#ifndef _TEACHING_BOX_DIALOG_PARENT_H_
#define _TEACHING_BOX_DIALOG_PARENT_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    DialogParent.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/09/08
//  Description:	对话框父类，用于控制对话框显示的位置及大小，同时提供国际化支持。
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/09/08
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "InternationalWidget.h"

class DialogParent:public InternationalWidget
{
public:
	DialogParent(QWidget* parent);
	virtual ~DialogParent();
	
protected:
	virtual void showEvent(QShowEvent *) override;

	virtual void SetSize();
	virtual void SetPosition();

private:
};

#endif