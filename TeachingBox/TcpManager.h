#ifndef _TEACHING_BOX_TCP_MANAGER_H_
#define _TEACHING_BOX_TCP_MANAGER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TcpManager.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/10/08
//  Description:	通过TCP与远程控制器建立连接，并发送指令，
		发送接收过程不可在子线程中进行，未避免因线程原因到时发送接收失败，可在主线程中初始化本类对象，
		并通过一适配器的信号与本类的相应函数进行连接，进而实现数据传输功能。
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/10/08
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QObject"
#include <memory>

class QHostAddress;
class QTcpSocket;
class RemoteParser;

class TcpManager:public QObject
{
	Q_OBJECT;

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

private slots:
	void SlotOnReceiveData();
	void SlotOnConnect();
	void SlotOnDisconnect();

private:
	void Init();
	void InitRemoteAddress();

private:
	QTcpSocket *m_tcpSocket = nullptr;
	std::unique_ptr<RemoteParser> m_remoteParser;
};

#endif