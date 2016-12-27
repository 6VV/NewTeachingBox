#ifndef _TEACHING_BOX_COORDINATE_ADAPTER_H_
#define _TEACHING_BOX_COORDINATE_ADAPTER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    CoordinateAdapter.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/12/27
//  Description:    坐标系变化矩阵适配器，用于调用第三方库函数
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/12/27
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "DataStruct.h"

class CoordinateAdapter
{
public:
	//坐标系示教方法：三点（含原点）
	//CartTeach From Three Points With Base
	static tPoseEuler CartTeachThreeBase(const tPoseEuler& point1, const tPoseEuler& point2, const tPoseEuler& point3);
	//坐标系示教方法：三点（无原点）
	//CartTeach From Three Points Without Base
	static tPoseEuler CartTeachThreeNoBase(const tPoseEuler& point1, const tPoseEuler& point2, const tPoseEuler& point3);

	//坐标系示教方法：一点（保持姿态）
	static tPoseEuler CartTeachOne(const tPositionCartesian& point1);

private:
};

#endif