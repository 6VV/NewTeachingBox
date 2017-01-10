#ifndef _TEACHING_BOX_VARIATE_READER_H_
#define _TEACHING_BOX_VARIATE_READER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    VariateReader.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/09
//  Description:    从xml文件中读取变量定义，仅用于测试
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/09
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

class QDomNode;

class VariateReader
{
public:
	static void InitVariatePrototype();
	
private:
	//static void InitVariate(const QDomNode& domNode);

private:
	class Initialization
	{
	public:
		Initialization();
	};

	static Initialization m_initlization;

};

#endif