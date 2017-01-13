#ifndef _LEXER_ROBOT_H_
#define _LEXER_ROBOT_H_

#include "..\QScintilla_gpl-2.9.3\Qt4Qt5\Qsci\qscilexercpp.h"
#include <string>

class LexerRobot:public QsciLexerCPP
{
public:
	LexerRobot(QObject* parent=0);
	~LexerRobot();

	virtual QStringList autoCompletionWordSeparators() const override;

	virtual const char * language() const override;

	virtual const char * wordCharacters() const override;

	virtual const char * keywords(int set) const override;

	void updateKeywords(const QStringList& keywords);
	void updateVariateWords(const QStringList& variateWords);

private:
	std::string m_keywords{};
	std::string m_variateWords{};
};

#endif