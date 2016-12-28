#include "stdafx.h"
#include "TToken.h"

//TToken::TToken(const TokenType type, const int lineNumber)
//	:m_type(type), m_lineNumber(lineNumber)
//{
//}


TToken::TToken(const int type, int lineNumber, const QString& name/*=""*/)
	: m_type(type)
	, m_lineNumber(lineNumber)
	, m_name(name)
{

}

TToken::~TToken()
{

}

int TToken::LineNumber() const
{
	return m_lineNumber;
}

QString TToken::Name() const
{
	return m_name;
}

const int TToken::Type() const
{
	return m_type;
}


void TToken::Type(const TokenType type)
{
	m_type = type;
}
