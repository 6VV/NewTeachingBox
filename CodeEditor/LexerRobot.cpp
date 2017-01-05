#include "stdafx.h"
#include "LexerRobot.h"



//
const char * LexerRobot::language() const
{
	return "Rb";
}

const char * LexerRobot::wordCharacters() const
{
	return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
}

const char * LexerRobot::keywords(int set) const
{
	if (set != 1)
		return 0;

	return m_keywords.c_str();
}

void LexerRobot::updateKeywords(const QStringList& keywords)
{
	m_keywords.clear();

	for (auto& key : keywords)
	{
		m_keywords.append(key.toStdString()).append(" ");
	}
}

QStringList LexerRobot::autoCompletionWordSeparators() const
{
	return{};
}

LexerRobot::LexerRobot(QObject* parent/*=0*/)
	:QsciLexerCPP(parent)
{
	m_keywords = "IF FOR SWITCH CASE DEFAULT";
}

LexerRobot::~LexerRobot()
{
}

