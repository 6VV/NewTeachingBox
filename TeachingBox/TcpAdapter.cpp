#include "stdafx.h"
#include "TcpAdapter.h"
#include "TcpManager.h"



TcpAdapter::TcpAdapter(QObject* parent /*= 0*/) :QObject(parent)
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
	connect(this, SIGNAL(SignalSendData(const QByteArray&)), TcpManager::GetInstance(), SLOT(SlotSendData(const QByteArray&)));
}
