#include "stdafx.h"
#include "Exception.h"



Exception::Exception(const QString& info)
{
	m_info = info;
}

QString Exception::GetInfo()
{
	return m_info;
}
