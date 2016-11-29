#include "stdafx.h"
#include "RemoteAdapterFactory.h"
#include "TcpAdapter.h"


RemoteAdapter* RemoteAdapterFactory::s_remoteAdapter{ nullptr };

RemoteAdapter* RemoteAdapterFactory::GetRemoteAdapter()
{
	if (s_remoteAdapter==nullptr)
	{
		s_remoteAdapter=new TcpAdapter();
	}

	return s_remoteAdapter;
}

void RemoteAdapterFactory::ResetRemoteAdapter(RemoteAdapter* remoteAdapter)
{
	if (s_remoteAdapter==remoteAdapter)
	{
		return;
	}

	if (s_remoteAdapter!=nullptr)
	{
		delete s_remoteAdapter;
	}

	s_remoteAdapter = remoteAdapter;
}

RemoteAdapterFactory::GC::~GC()
{
	if (RemoteAdapterFactory::s_remoteAdapter!=nullptr)
	{
		delete RemoteAdapterFactory::s_remoteAdapter;
		RemoteAdapterFactory::s_remoteAdapter = nullptr;
	}
}
