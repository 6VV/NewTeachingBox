﻿#ifndef _SCI_CODE_EDITOR_H_
#define _SCI_CODE_EDITOR_H_

#include <QtWidgets/QMainWindow>
#include "Qsci/qsciscintilla.h"
#include <vector>

class SciRobot;
class LexerRobot;
class QKeyEvent;

class SciCodeEditor : public QsciScintilla
{
    Q_OBJECT

private:
	enum MarkerNumber
	{
		EXECUTE_MARKER = 0,
		WRONG_MARKER=1,
	};
	
	enum MarginNumber
	{
		FLAGS_MARGIN=1,
		LINE_NUMBER_MARGIN,
		FOLD_MARGIN,
	};

	enum IndicatorNumber
	{
		SEARCH_INDICATOR,
	};

public:
    SciCodeEditor(QWidget *parent = nullptr);

	//virtual void keyPressEvent(QKeyEvent *e) override;

	void clearWrongLine();	/*清除错误行标志*/
	void clearSearchIndicator(); /*清除搜索标志*/
	QString currentLineText() const;	/*当前行文本*/
	int cursorLine() const;	/*当前行*/

	void defineWrongLineMarker(const QString& iconPath);

	void format();	/*文本格式化*/

	void highlightPCLine(int lineNumber);	/*高亮显示执行行*/
	void highlightWrongLine(int lineNumber);	/*高亮显示错误行*/

	void selectAll();
	void search(const QString& word);

	void updateCurrentLine(const QString& text);	/*更新当前行文本*/
	void updateKeywords(const QStringList& keywords);	/*更新关键词*/
	void updateVariateWords(const QStringList& variateWords);	/*更新变量集合*/

	void insertTextBeforeLine(const QString& text);	/*插入文本*/

private:
	void initAutoCompletionSetting();	/*设置自动完成*/
	void initBraceMatching();	/*设置括号匹配*/
	void initCaretSetting();	/*设置插入符号*/
	void initKeywordColor();			/*设置关键词颜色*/
	void initFoldingSetting();	/*设置折叠*/
	void initIndentSetting();	/*设置缩进*/
	void initMarginSetting();	/*设置边界*/
	void initIndicator();	/*设置指示器*/

	void updateMargin();	/*刷新边界标志*/

private:
	class Range
	{
	public:
		Range(int lineFrom, int indexFrom, int lineTo, int indexTo);

		int lineFrom=0;
		int lineTo = 0;
		int indexFrom = 0;
		int indexTo = 0;
	};

private:
	SciRobot *m_apis;
	LexerRobot* m_lexer;
	std::vector<Range> m_rangesSearched{};
	int m_executeLine = 0;
};

#endif
