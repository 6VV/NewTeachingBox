#include "stdafx.h"
#include "LexerRobot.h"



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
	if (set == 2)
	{
		return m_variateWords.c_str();
	}

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

void LexerRobot::updateVariateWords(const QStringList& variateWords)
{
	m_variateWords.clear();

	for (auto& key : variateWords)
	{
		m_variateWords.append(key.toStdString()).append(" ");
	}
}

QStringList LexerRobot::autoCompletionWordSeparators() const
{
	return{};
}

LexerRobot::LexerRobot(QObject* parent/*=0*/)
	:QsciLexerCPP(parent)
{
	m_keywords = "IF ELSEIF FOR STEP TO SWITCH CASE DEFAULT";
}

LexerRobot::~LexerRobot()
{
}

