#ifndef _TEACHING_BOX_REMOTE_ADAPTER_FACTORY_H_
#define _TEACHING_BOX_REMOTE_ADAPTER_FACTORY_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    RemoteFactory.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/18
//  Description:    远程适配器工厂，采用工厂模式，生成远程适配器类，采用工厂模式主要便于之后更换适配器类,同时便于进行单元测试
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/11/18
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <memory>

class RemoteAdapter;

class RemoteAdapterFactory
{
public:
	static RemoteAdapter* GetRemoteAdapter();

	/*重新设置当前RemoteAdapter，本函数仅用于MockTest*/
	static void ResetRemoteAdapter(RemoteAdapter* remoteAdapter);

private:
	static RemoteAdapter* s_remoteAdapter;

private:
	class GC
	{
	public:
		~GC();
	};

	static GC s_gc;
};

#endif