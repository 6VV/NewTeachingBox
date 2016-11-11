#ifndef _TEACHING_BOX_MACRO_WIDGET_MOVC_H_
#define _TEACHING_BOX_MACRO_WIDGET_MOVC_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    MacroWidgetMovc.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/10/14
//  Description:	用于生成MOVL命令的编辑窗口
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/10/14
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "MacroWidgetParent.h"

class MacroWidgetMovc:public MacroWidgetParent
{
	Q_OBJECT

public:
	MacroWidgetMovc(const QString& macroText, QWidget* parent = nullptr);
	virtual ~MacroWidgetMovc();

private:
	virtual QString MacroName() override;

};

#endif