#ifndef _TEACHING_BOX_MACRO_WIDGET_MOVL_H_
#define _TEACHING_BOX_MACRO_WIDGET_MOVL_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    MacroWidgetMovl.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/10/11
//  Description:	用于生成MOVL命令的编辑窗口
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/10/11
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "MacroWidgetParent.h"

class MacroWidgetMovl:public MacroWidgetParent
{
	Q_OBJECT

public:
	MacroWidgetMovl(const QString& macroText,QWidget* parent=nullptr);
	virtual ~MacroWidgetMovl();
	
private:
	void Init();

	virtual void OnConfirm() override;
	virtual void UpdateText() override;

};

#endif