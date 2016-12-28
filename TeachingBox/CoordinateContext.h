#ifndef _TEACHING_BOX_COORDINATE_CONTEXT_H_
#define _TEACHING_BOX_COORDINATE_CONTEXT_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    Coordinate.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/12/27
//  Description:    坐标系环境变量
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/12/27
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QString"
#include "DataStruct.h"

class CoordinateContext
{
public:
	static const QString WorldRefSysName();

	static tPoseEuler WorldRefSysValue();
};

#endif