#include "stdafx.h"
#include "Exception.h"



Exception::Exception(const QString& info)
{
	m_info = info;
}

Exception::Exception()
{

}

QString Exception::GetInfo()
{
	return m_info;
}
