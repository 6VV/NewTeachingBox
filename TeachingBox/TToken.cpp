#include "stdafx.h"
#include "TToken.h"

TToken::TToken(const TokenType type, const int lineNumber)
	:m_type(type), m_lineNumber(lineNumber)
{
}

TToken::~TToken()
{

}

const int TToken::GetLineNumber() const
{
	return m_lineNumber;
}

const TToken::TokenType TToken::GetType() const
{
	return m_type;
}


void TToken::SetType(const TokenType type)
{
	m_type = type;
}
