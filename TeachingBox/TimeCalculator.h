#ifndef _TEACHING_BOX_TIME_CALCULATOR_H_
#define _TEACHING_BOX_TIME_CALCULATOR_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TimeCalculator.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/06
//  Description:    计时器，主要用于方便测试代码运行时间
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/06
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <chrono>

class TimeCalculator
{
public:
	static void Start();
	static void End(const QString& text="");

private:
	static std::chrono::steady_clock::time_point m_startTime;
};

#endif