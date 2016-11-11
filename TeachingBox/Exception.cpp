#include "stdafx.h"
#include "Exception.h"



Exception::Exception(const QString& info)
{
	m_info = info;
}

Exception::Exception()
{

}

QString Exception::Info()
{
	return m_info;
}
