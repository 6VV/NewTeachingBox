#ifndef _TEACHING_BOX_MACRO_H_
#define _TEACHING_BOX_MACRO_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    Macro.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/09/08
//  Description:	用于记录所有宏命令及分类字符串，包括每种分类下的所有类型，以及每种类型下的所有命令
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/09/08
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <vector>
#include <set>
#include "QString"
#include <map>

class Macro
{
private:
	/*分类*/
	static const QString CATEGORY_MOVEMENT;
	static const QString CATEGORY_FUNCTION;
	static const QString CATEGORY_IO;
	static const QString CATEGORY_WELD;

	/*类型*/
	static const QString TYPE_MOVEMENT;

	static const QString TYPE_MATH;
	static const QString TYPE_STRUCTURE;
	static const QString TYPE_PROGRAM;
	static const QString TYPE_FUNCTION;
	static const QString TYPE_OTHERS;

	static const QString TYPE_DIGITAL;
	static const QString TYPE_ANALOG;

	static const QString TYPE_ARC_WELDING;
	static const QString TYPE_SPOT_WELDING;

public:
	/*命令*/
	static const QString MACRO_MOVL;
	static const QString MACRO_MOVJ;
	static const QString MACRO_MOVJX;
	static const QString MACRO_MOVC;
	static const QString MACRO_MOVX;
	static const QString MACRO_MOVY;
	static const QString MACRO_MOVZ;
	static const QString MACRO_ROTX;
	static const QString MACRO_ROTY;
	static const QString MACRO_ROTZ;

	static const QString MACRO_SIN;
	static const QString MACRO_COS;
	static const QString MACRO_TAN;
	static const QString MACRO_SQRT;

	static const QString MACRO_GOSUB;
	static const QString MACRO_FOR;
	static const QString MACRO_IF;
	static const QString MACRO_ELSEIF;
	static const QString MACRO_SWITCH;
	static const QString MACRO_CASE;
	static const QString MACRO_BREAK;

	static const QString MACRO_ABORT;

	static const QString MACRO_WAIT;

	static const QString MACRO_SET_TOOLFRAME;
	static const QString MACRO_SET_USERFRAME;

	static const QString MACRO_DIN;
	static const QString MACRO_DOUT;
	static const QString MACRO_AIN;
	static const QString MACRO_AOUT;

	static const QString MACRO_ARC_ON;
	static const QString MACRO_ARC_OFF;
	static const QString MACRO_SET_ARC;

	static const QString MACRO_SPOT_ON;
	static const QString MACRO_SPOT_OFF;
	static const QString MACRO_SET_SPOT;

public:
	static const std::vector<QString> CATEGORYS;
	static const std::map<QString, std::set<QString>> TYPE_MAP;
	static const std::map<QString, std::set<QString>> MACRO_MAP;
	static const std::map<QString, QString> TEXT_MAP;

};

#endif