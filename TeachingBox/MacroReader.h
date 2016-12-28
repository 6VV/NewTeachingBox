#ifndef _TEACHING_BOX_MACRO_READER_H_
#define _TEACHING_BOX_MACRO_READER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    MacroReader.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/12/28
//  Description:    读取命令文档,并初始化命令信息
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/12/28
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

class MacroReader
{
private:
	static void InitMacro();

private:
	class Initialization
	{
	public:
		Initialization();
	};

	static Initialization m_initlization;
};

#endif