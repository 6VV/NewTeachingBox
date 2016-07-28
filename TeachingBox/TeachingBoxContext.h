#ifndef _TEACHING_BOX_CONTEXT_H_
#define _TEACHING_BOX_CONTEXT_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TeachingBoxContext.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/07/28
//  Description:	用于记录当前示教盒的一些全局状态
//  Others:			
//  History:
//    <author>      刘巍 
//    <time>        2016/07/28
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

namespace TeachingBoxContext
{
	enum ExecuteMode
	{
		AUTO,
		STEP,
		MANUAL,
	};

	void SetExecuteMode(ExecuteMode mode);
}


#endif