#ifndef _TEACHING_BOX_CONTEXT_H_
#define _TEACHING_BOX_CONTEXT_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    Context.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/09/05
//  Description:	用于记录整个示教盒的全局变量
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/09/05
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "ProjectContext.h"
#include "InterpreterContext.h"

class Context
{
public:
	static ProjectContext projectContext;
	static InterpreterContext interpreterContext;
};

#endif