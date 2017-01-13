#include "stdafx.h"
#include "SciRobot.h"



SciRobot::SciRobot(QsciLexer* lexer)
	:QsciAPIs(lexer)
{

}

void SciRobot::updateKeywords(const QStringList& keywords)
{
	m_keywords = keywords;

	for (auto word : keywords)
	{
		add(word);
	}
}

void SciRobot::updateVariates(const QStringList &entries)
{
	clear();

	for (auto word:m_keywords)
	{
		add(word);
	}

	for (auto word:entries)
	{
		add(word);
	}
}
