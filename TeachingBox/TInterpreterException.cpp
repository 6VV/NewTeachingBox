#include "stdafx.h"
#include "TInterpreterException.h"
#include "Context.h"

const QMap<int, QString> TInterpreterException::Exception_TEXT
{
	{ FOR_SENTENCE_SHOULD_END_WITH_NEXT, "for sentence should end with next" },
	{ FOR_SENTENCE_SHOULD_USE_INTERGER_OR_DOUBLE, "for sentence should use interger or double" },
	{ IF_SENTENCE_SHOULD_END_WITH_ENDIF, "if sentence should end with endif" },
	{ IF_SENTENCE_SHOULD_WITH_BOOL, "if sentence should  with bool" },
	{ LOSE_COMMA, "lose comma" },
	{ MOVL_SHOULD_WITH_POSITOIN_DYNAMIC_OVERLAP, "movl should should be with position,dynamic,overlap" },
	{ MISS_LEFT_BRACE, "miss left brace" },
	{ MISS_RIGHT_BRACE, "miss right brace" },
	{ NOT_FIND_RIGHT_BRACKET, "not find right bracket" },
	{ NEGATION_SHOULD_WITH_BOOL, "\"!\" should with bool" },
	{ NEGATIVE_SHOULD_WITH_INT_OR_DOUBLE, "\"-\" should with integer or double" },
	{ NOT_FIND_VARIATE, "not find variate" },
	{ NOT_MOVL_SENTENCE, "not movl sentence" },
	{ NOT_PROGRAM_NAME, "not program name" },
	{ ONLY_NUMBER_COULD_TAKE_ARITHMETICAL_OPERATION, "only number could take part in arithmetical opration" },
	{ ONLY_NUMBER_COULD_TAKE_RELATIONAL_OPERATION, "only number could take part in relational opration" },
	{ ONLY_BOOL_COULD_TAKE_LOGICAL_OPERATION, "only bool could take part in logical opration" },
	{ ONLY_INTERGER_COULD_TAKE_MOD_OPERATION, "only interger could take part in mod opration" },
	{ SENTENCE_NOT_END_WITH_ABNORMAL_END, "sentence not end with abnormal end" },
	{ SENTENCE_SHOULD_END_WITH_LINE_BREAK, "sentence should end with line break" },
	{ TYPE_NOT_MATCH, "type not match" },
	{ UNKNOWN_SENTENCE, "unknown sentence" },
	{ UNKNOWN_VARIATE, "unknown variate" },
	{ UNKNOWN_TOKEN, "unknown token" },
	{ WRONG_GRAMMAR, "wrong grammar" },
	{ WRONG_PARAMETER, "wrong parameter" },
};

TInterpreterException::TInterpreterException(const InterpreterExceptionCode id, const int lineNumber, const QString& text/*=""*/)
	: m_id(id), m_lineNumber(lineNumber), m_text(text)
{

}

QString TInterpreterException::Info()
{
	const int SIZE_ADDED = 2;

	QString text = Format("Information:", SIZE_ADDED) + Exception_TEXT[m_id] + "\n"
		+ Format("Program:", SIZE_ADDED) + Context::projectContext.ProgramLoading() + "\n"
		+ Format("Line Number:", SIZE_ADDED) + QString::number(m_lineNumber);

	if (m_text.size() > 0)
	{
		text.append("\n" + Format("Text:", SIZE_ADDED) + m_text);
	}
	return text;
}

int TInterpreterException::LineNumber() const
{
	return m_lineNumber;
}

inline
QString TInterpreterException::Format(const QString& text, int size)
{
	QString result{ text };
	for (int i = 0; i < size;++i)
	{
		result.append(" ");
	}

	return result;
}

