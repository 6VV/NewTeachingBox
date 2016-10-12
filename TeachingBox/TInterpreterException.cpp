#include "stdafx.h"
#include "TInterpreterException.h"


const QMap<int, QString> TInterpreterException::Exception_TEXT
{
	{ UNKNOW_TOKEN, "unknown token" },
	{ WRONG_GRAMMAR, "wrong grammar" },
	{ NOT_FIND_RIGHT_BRACKET, "not find right bracket" },
	{ NEGATION_SHOULD_WITH_BOOL, "\"!\" should with bool" },
	{ NEGATIVE_SHOULD_WITH_INT_OR_DOUBLE, "\"-\" should with integer or double" },
	{ NOT_FIND_VARIATE, "not find variate" },
	{ ONLY_NUMBER_COULD_TAKE_ARITHMETICAL_OPERATION, "only number could take part in arithmetical opration" },
	{ ONLY_NUMBER_COULD_TAKE_RELATIONAL_OPERATION, "only number could take part in relational opration" },
	{ ONLY_BOOL_COULD_TAKE_LOGICAL_OPERATION, "only bool could take part in logical opration" },
	{ ONLY_INTERGER_COULD_TAKE_MOD_OPERATION, "only interger could take part in mod opration" },
	{ SENTENCE_NOT_END_WITH_ABNORMAL_END, "sentence not end with abnormal end" },
	{ SENTENCE_SHOULD_END_WITH_LINE_BREAK, "sentence should end with line break" },
	{ TYPE_NOT_MATCH, "type not match" },
	{ FOR_SENTENCE_SHOULD_END_WITH_NEXT, "for sentence should end with next" },
	{ FOR_SENTENCE_SHOULD_USE_INTERGER_OR_DOUBLE, "for sentence should use interger or double" },
	{ IF_SENTENCE_SHOULD_END_WITH_ENDIF, "if sentence should end with endif" },
	{ IF_SENTENCE_SHOULD_WITH_BOOL, "if sentence should  with bool" },
	{ NOT_MOVL_SENTENCE, "not movl sentence" },
	{ MOVL_SHOULD_WITH_POSITOIN_DYNAMIC_OVERLAP, "movl should should be with position,dynamic,overlap" },
	{ LOSE_COMMA, "lose comma" },
	{ NOT_PROGRAM_NAME, "not program name" },
	{ UNKNOWN_SENTENCE, "unknown sentence" },
};

TInterpreterException::TInterpreterException(const InterpreterExceptionCode id, const int lineNumber, const QString& text/*=""*/)
	: m_id(id), m_lineNumber(lineNumber), m_text(text)
{

}

QString TInterpreterException::GetInfo()
{
	QString text = "Information: " + Exception_TEXT[m_id] + "\nLine Number: " + QString::number(m_lineNumber);

	if (m_text.size() > 0)
	{
		text.append("\nText: " + m_text);
	}
	return text;
}

int TInterpreterException::GetLineNumber() const
{
	return m_lineNumber;
}

