#ifndef _TEACHING_BOX_T_TOKEN_H_
#define _TEACHING_BOX_T_TOKEN_H_

#include "TTokenType.h"

class TToken
{
protected:
	typedef TTokenType::Type TokenType;

public:
	TToken(const int type, int lineNumber, const QString& name="");
	virtual ~TToken();

	int LineNumber() const;

	QString Name() const;

	const int Type() const;
	void Type(const TokenType type);

private:
	int m_type;
	int m_lineNumber;
	QString m_name;
};

#endif