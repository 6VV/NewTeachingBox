#ifndef _TEACHING_BOX_REMOTE_FEEDBACK_CONTROLLER_H_
#define _TEACHING_BOX_REMOTE_FEEDBACK_CONTROLLER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    RemoteFeedbackController.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/28
//  Description:    用于控制接收到远程命令后的相关操作。
		维护一个集合，用于存储远程命令监听器类相关对象，当接收到远程命令后，依次调用远程命令的相关操作。
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/11/28
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <list>
#include "DataStruct.h"

class IRemoteFeedbackListener;

class RemoteFeedbackController
{
public:
	void AddListener(IRemoteFeedbackListener* listener);
	void DeleteListener(IRemoteFeedbackListener* listener);

	static RemoteFeedbackController* GetInstance();

public:
	void OnReseivePosition(const tAxesAllPositions& position);

private:
	RemoteFeedbackController()=default;
	RemoteFeedbackController(const RemoteFeedbackController&) = delete;
	RemoteFeedbackController& operator=(const RemoteFeedbackController&) = delete;
	~RemoteFeedbackController()=default;

private:
	std::list<IRemoteFeedbackListener*> m_listeners;
};

#endif