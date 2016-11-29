#ifndef _TEACHING_BOX_REMOTE_ADAPTER_H_
#define _TEACHING_BOX_REMOTE_ADAPTER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    RemoteAdapter.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/18
//  Description:    远程通信适配器，提供远程通信相关接口，包括数据发送与接收，本类不可实例化，可作为相关通信适配器的父类。
		构建适配器类的主要原因在于多线程通信时会发生数据无法正常传输现象，故通过适配器提供的信号与实际通信类进行连接，进而实现多线程下的正常通信。
		构建本类的另两个作用为配合工厂方法模式和MockTest。
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/11/18
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <QByteArray>
#include "QObject"

class RemoteAdapter:public QObject
{
	Q_OBJECT

	friend class RemoteAdapterFactory;

public:
	virtual void SendData(const QByteArray& data)=0;

protected:
	virtual ~RemoteAdapter() = default;

signals:
	void SignalSendData(const QByteArray& data);
};

#endif