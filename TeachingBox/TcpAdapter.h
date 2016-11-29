#ifndef _TEACHING_BOX_TCP_ADAPTER_H_
#define _TEACHING_BOX_TCP_ADAPTER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TcpAdapter.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/10/08
//  Description:	TCP适配器，为防止因线程原因导致的TCP传输失败，采用本适配器的信号与实际的TCP传输函数进行连接，
		使得能够通过调用本适配器的相应函数跨线程进行数据传输
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/10/08
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "RemoteAdapter.h"

class TcpAdapter:public RemoteAdapter
{
	Q_OBJECT

	friend class RemoteAdapterFactory;

public:
	virtual void SendData(const QByteArray& data) override;

private:
	TcpAdapter();
	TcpAdapter(const TcpAdapter&);
	TcpAdapter& operator=(const TcpAdapter&);
	~TcpAdapter();

private:
	void Init();
};

#endif