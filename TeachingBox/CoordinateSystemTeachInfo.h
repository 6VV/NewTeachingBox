#ifndef _TEACHING_BOX_COORDINATE_SYSTEM_TEACH_INFO_H_
#define _TEACHING_BOX_COORDINATE_SYSTEM_TEACH_INFO_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    CoordinateSystemTeachInfo.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/18
//  Description:    坐标系示教用相关信息
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/18
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "DataStruct.h"

class CoordinateSystemTeachInfo
{
public:
	enum Method
	{
		REF_SYS_THREE_POINTS_WITH_ORIGIN,
		REF_SYS_THREE_POINTS_WITHOUT_ORIGIN,
		REF_SYS_ONE_POINT_KEEP_ORIENTATION,
		TOOL_SYS_FOUR_POINTS,
		ONE_POINT_6D,
	};
	enum Orientation
	{
		X,
		Y,
		Z,
		XY,
		YZ,
		ZX,
		IX,	/*X反向*/
		IY,
		IZ,
	};
	struct CoorSysInfo
	{
		Orientation orientation;
		std::shared_ptr<tPoseEuler> poseEuler;
	};

	void UpdatePoseEuler(const tPoseEuler& poseEuler);
	void UpdateOrientation(Orientation orientation);

	void AddCoorSysInfo(const CoorSysInfo& coorInfo);
	void AddPoseEuler(const tPoseEuler& poseEuler);

	int index = -1;
	Method method=REF_SYS_THREE_POINTS_WITH_ORIGIN;
	std::vector<CoorSysInfo> values{};
};

#endif