#ifndef _TEACHING_BOX_T_INTERPRETER_INFO_H_
#define _TEACHING_BOX_T_INTERPRETER_INFO_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TInterpreterInfo.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/17
//  Description:    记录解释器相关信息，可用于国际化翻译
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/17
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QObject"

class TInterpreterInfo:public QObject
{
	Q_OBJECT

public:
	static QString GetInfo(int id);

	static QString InformationText();
	static QString ProgramText();
	static QString LineNumberText();
};

#endif