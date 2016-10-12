#ifndef _TEACHING_BOX_I_SCREEN_NETWORK_H_
#define _TEACHING_BOX_I_SCREEN_NETWORK_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    IScreenNetwork.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/10/08
//  Description:	网络界面接口，用于控制网络界面相关操作的回调函数
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/10/08
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

class QString;

class IScreenNetwork
{
public:
	virtual void OnNewAddress(const QString& address)=0;
};

#endif