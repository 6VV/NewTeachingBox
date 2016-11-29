#ifndef _TEACHING_BOX_T_TOKEN_H_
#define _TEACHING_BOX_T_TOKEN_H_

#include "TTokenType.h"

class TToken
{
protected:
	typedef TTokenType::Type TokenType;

public:
	TToken(const TokenType type, int lineNumber, const QString& name="");
	virtual ~TToken();

	int LineNumber() const;

	QString Name() const;

	const TokenType Type() const;
	void Type(const TokenType type);

private:
	TokenType m_type;
	int m_lineNumber;
	QString m_name;
};

#endif