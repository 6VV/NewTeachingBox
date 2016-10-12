#ifndef _TEACHING_BOX_TCP_MANAGER_H_
#define _TEACHING_BOX_TCP_MANAGER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TcpManager.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/10/08
//  Description:	用于与远程控制器建立连接，并发送指令
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/10/08
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QObject"
#include "SingleTon.h"

class QHostAddress;
class QTcpSocket;
class RemoteParser;

class TcpManager:public QObject
{
	Q_OBJECT;

	friend SingleTon<TcpManager>;

	static const int PORT = 1234;

public:
	static TcpManager* GetInstance();

	static QString LocalIPAddress();

private:
	TcpManager();
	TcpManager(const TcpManager&)=delete;
	TcpManager& operator=(const TcpManager&)=delete;
	~TcpManager();

public:
	void SendData(const QByteArray& data);
	void ConnectAddress(const QString& address);

public slots:
	void SlotSendData(const QByteArray& data);

private slots:
	void SlotOnReceiveData();
	void SlotOnConnect();
	void SlotOnDisconnect();

private:
	void Init();
	void InitRemoteAddress();

private:
	QTcpSocket *m_tcpSocket = nullptr;

	RemoteParser *m_remoteParser=nullptr;
};

#endif