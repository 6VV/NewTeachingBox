#include "stdafx.h"
#include "TcpManager.h"
#include "QHostInfo"
#include "RemoteParser.h"



TcpManager* TcpManager::GetInstance()
{
	return SingleTon<TcpManager>::GetInstance();
}

TcpManager::TcpManager()
	:m_tcpSocket(new QTcpSocket)
	, m_remoteParser(new RemoteParser)
{
	Init();
}

TcpManager::~TcpManager()
{
	m_tcpSocket->close();
	delete m_tcpSocket;
	delete m_remoteParser;

	m_tcpSocket = nullptr;
	m_remoteParser = nullptr;
}

void TcpManager::SendData(const QByteArray& data)
{
	if (m_tcpSocket->state() == QAbstractSocket::ConnectedState)
	{
		m_tcpSocket->write(data);
	}
}



void TcpManager::ConnectAddress(const QString& address)
{
	QHostAddress hostAddress;
	hostAddress.setAddress(address);
	m_tcpSocket->connectToHost(hostAddress, PORT);
}

void TcpManager::SlotSendData(const QByteArray& data)
{
	SendData(data);
}

void TcpManager::SlotOnReceiveData()
{
	while (m_tcpSocket->bytesAvailable() > 0)
	{
		QByteArray data;
		data.resize(static_cast<int>(m_tcpSocket->bytesAvailable()));
		m_tcpSocket->read(data.data(), data.size());
		m_remoteParser->ParseCommands(data);
	}
}

void TcpManager::SlotOnConnect()
{

}

void TcpManager::SlotOnDisconnect()
{

}

void TcpManager::Init()
{
	InitRemoteAddress();

	connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(SlotOnConnect()));
	connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(SlotOnDisconnect()));
	connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(SlotOnReceiveData()));
}

void TcpManager::InitRemoteAddress()
{
	ConnectAddress(LocalIPAddress());
}

QString TcpManager::LocalIPAddress()
{
	/*添加IP地址*/
	QString strAddress;
	QHostInfo hostInfo = QHostInfo::fromName(QHostInfo::localHostName());

	for each (auto var in hostInfo.addresses())
	{
		if (var.protocol() == QAbstractSocket::IPv4Protocol)
		{
			strAddress = var.toString();
			break;
		}
	}
	return strAddress;
}