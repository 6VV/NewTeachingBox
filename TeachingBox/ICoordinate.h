#ifndef _TEACHING_BOX_I_COORDINATE_H_
#define _TEACHING_BOX_I_COORDINATE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ICoordinate.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/12/27
//  Description:    提供坐标系接口，用于回调函数
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/12/27
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

struct tPoseEuler;

class ICoordinate
{
public:
	virtual ~ICoordinate(){};

	virtual void OnReceive(const tPoseEuler& poseEuler)=0;
};

#endif