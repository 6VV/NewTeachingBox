#ifndef _TEACHING_BOX_C_T_LEXER_H_
#define _TEACHING_BOX_C_T_LEXER_H_

#include <memory>
#include <vector>
#include "TTokenType.h"

class TToken;

class TLexer
{
private:
	typedef TTokenType::Type TYPE;

public:
	TLexer(const QString& text);
	~TLexer();
	
	const std::shared_ptr<TToken> GetToken() const;
	const std::shared_ptr<TToken> PeekToken() const;
	void Parse();

	void UnGetToken();

private:
	void GetInterger(QString &text);
	void GetId(QString& text);

	const bool IsDigit(const char c) const;
	const bool IsLetter(const char c) const;
	const bool IsIdText(const char c) const;

	void PushToken(const int type,const QString& name="");
	const bool CheckPushDigit(const char c);
	const bool CheckPushId(const char c);
	const bool CheckPushKeyword(const QString& text);
	bool CheckPushXmlKeyword(const QString& text);	/*判断是否是xml中记录关键字*/
	const bool CheckPushReserveValue(const TYPE type);
	const bool CheckPushOtherToken(const char);

	void PushTokenNote();
	void PushTokenString();
	void PushTokenLess();
	void PushTokenGreat();
	void PushTokenNot();
	void PushTokenEqual();

	void SkipCharInSameLine();

	bool IsEofOrEol(char c);

	void ThrowException_UnknownToken(const QString& text);

private:
	std::vector < std::shared_ptr<TToken>> m_tokens;
	mutable unsigned m_index=0;

private:
	class Reader
	{
	public:
		Reader(const QString& text);

		const char GetNextChar();
		const char GetCurrentChar() const;
		const int GetLineNumber() const;

		const bool IsEof() const;

		const char PeekChar(const int index) const;

		void SkipBlank();

		void UnGetChar();
	private:
		const bool IsBlank(const char c) const;

	private:
		const QString* m_text = nullptr;
		int m_index = 0;
		int m_lineNumber = 1;
	};

	Reader m_reader;
};

#endif