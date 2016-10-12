#ifndef _TEACHING_BOX_TCP_ADAPTER_H_
#define _TEACHING_BOX_TCP_ADAPTER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TcpAdapter.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/10/08
//  Description:	TCP适配器，用于将TCP线程分离开来，通过信号、槽机制控制指令的传输
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/10/08
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QObject"

class TcpAdapter:public QObject
{
	Q_OBJECT
public:
	TcpAdapter(QObject* parent = 0);
	~TcpAdapter();

	void SendData(const QByteArray& data);

signals:
	void SignalSendData(const QByteArray& data);

private:
	void Init();
};

#endif