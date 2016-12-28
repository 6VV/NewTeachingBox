#ifndef _TEACHING_BOX_MACRO_WIDGET_COMMON_H_
#define _TEACHING_BOX_MACRO_WIDGET_COMMON_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    MacroWidgetCommon.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/12/28
//  Description:    通用命令控件，未经特殊定义的命令采用本控件进行生成
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/12/28
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "MacroWidgetParent.h"
#include "MacroInfo.h"


class MacroWidgetCommon:public MacroWidgetParent
{
public:
	MacroWidgetCommon(const MacroInfo& macroInfo,QWidget* parent=0);
	
private:
	virtual QString MacroName() override;
	MacroInfo m_macroInfo;
};

#endif