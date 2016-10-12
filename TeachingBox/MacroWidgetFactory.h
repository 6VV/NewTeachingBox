#ifndef _TEACHING_BOX_MACRO_WIDGET_FACTORY_H_
#define _TEACHING_BOX_MACRO_WIDGET_FACTORY_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    MacroWidgetFactory.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/10/11
//  Description:	用于生产各种命令的编辑窗口
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/10/11
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

class QWidget;
class QString;

class MacroWidgetFactory
{
public:
	static QWidget* CreateMacroWidget(const QString& macro, QWidget* parent = nullptr);
	
};

#endif