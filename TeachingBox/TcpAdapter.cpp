#include "stdafx.h"
#include "TcpAdapter.h"
#include "TcpManager.h"
#include "RemoteParser.h"



TcpAdapter::TcpAdapter() 
{
	Init();
}

TcpAdapter::~TcpAdapter()
{

}

void TcpAdapter::SendData(const QByteArray& data)
{
	emit(SignalSendData(data));
}


void TcpAdapter::Init()
{
	connect(this, &TcpAdapter::SignalSendData, TcpManager::GetInstance(), &TcpManager::SendData);
}
