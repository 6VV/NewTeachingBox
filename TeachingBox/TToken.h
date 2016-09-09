#ifndef _TEACHING_BOX_T_TOKEN_H_
#define _TEACHING_BOX_T_TOKEN_H_

#include "TTokenType.h"

class TToken
{
protected:
	typedef TTokenType::Type TokenType;

public:
	TToken(const TokenType type, const int lineNumber);
	virtual ~TToken();

	const int GetLineNumber() const;
	const TokenType GetType() const;
	void SetType(const TokenType type);

private:
	TokenType m_type;
	int m_lineNumber;
};

#endif