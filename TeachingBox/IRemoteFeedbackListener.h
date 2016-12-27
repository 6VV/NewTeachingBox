#ifndef _TEACHING_BOX_I_REMOTE_FEEDBACK_LISTENER_H_
#define _TEACHING_BOX_I_REMOTE_FEEDBACK_LISTENER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    IRemoteFeedback.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/28
//  Description:    接口类，用于提供处理远程命令的一些接口函数。
		当获取到远程命令后，在RemoteParser类中进行处理，并调用相应的接口函数。
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/11/28
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "DataStruct.h"


class IRemoteFeedbackListener
{
public:
	virtual ~IRemoteFeedbackListener(){};

	virtual void OnReseivePosition(const tAxesAllPositions& /*position*/ = {}){};
	virtual void OnReseivePose(const tPoseEuler& /*position*/ = {}){};
};

#endif