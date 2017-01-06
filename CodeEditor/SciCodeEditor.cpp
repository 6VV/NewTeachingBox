#include "stdafx.h"
#include "LexerRobot.h"
#include "SciCodeEditor.h"
#include "..\QScintilla_gpl-2.9.3\Qt4Qt5\Qsci\qsciapis.h"
#include <assert.h>

#include "minus_icon.xpm"
#include "plus_icon.xpm"

SciCodeEditor::SciCodeEditor(QWidget *parent)
	: QsciScintilla(parent)
{
	m_lexer = new LexerRobot(this);	/*解析器*/
	this->setLexer(m_lexer);	/*设置解析器*/
	m_apis = new QsciAPIs(m_lexer);	/*自动完成入口*/

	this->setUtf8(true);	/*设置编码为utf-8*/

	initAutoCompletionSetting();	/*自动完成*/
	initBraceMatching();	/*括号匹配*/
	initCaretSetting();	/*插入符号*/
	initFoldingSetting();	/*设置折叠*/
	initIndentSetting();	/*设置缩进*/
	initMarginSetting();	/*设置边界*/
	initIndicator();	/*设置指示器*/
	
	setTabWidth(indentationWidth());	/*设置Tab宽度*/
}


//void SciCodeEditor::keyPressEvent(QKeyEvent *e)
//{
//	auto key = e->key();
//	qDebug() << key;
//	QsciScintilla::keyPressEvent(e);
//}

void SciCodeEditor::clearWrongLine()
{
	markerDeleteAll(WRONG_MARKER);
}

void SciCodeEditor::clearSearchIndicator()
{
	for (auto range : m_rangesSearched)
	{
		clearIndicatorRange(range.lineFrom, range.indexFrom, range.lineTo, range.indexTo, SEARCH_INDICATOR);
	}
}

QString SciCodeEditor::currentLineText() const
{
	return text(cursorLine());
}

void SciCodeEditor::highlightPCLine(int lineNumber)
{
	markerDeleteAll(EXECUTE_MARKER);
	markerAdd(lineNumber, EXECUTE_MARKER);
	m_executeLine = lineNumber;
}

void SciCodeEditor::highlightWrongLine(const int lineNumber)
{
	markerAdd(lineNumber, WRONG_MARKER);
}

void SciCodeEditor::selectAll()
{
	setSelection(0, 0, lines(), 0);
}

void SciCodeEditor::search(const QString& word)
{
	clearSearchIndicator();

	int length = word.length();
	if (length==0)
	{
		return;
	}
	for (int line = 0; line < lines(); ++line)
	{
		auto lineText = text(line);
		int index = 0;

		while (index != -1)
		{
			if (index >= lineText.length())
			{
				break;
			}
			index = lineText.indexOf(word, index);
			if (index == -1)
			{
				break;
			}
			m_rangesSearched.push_back(Range(line, index, line, index + length));
			fillIndicatorRange(line, index, line, index + length, SEARCH_INDICATOR);
			index += length;
		}
	}
}

void SciCodeEditor::updateCurrentLine(const QString& text)
{
	int line = cursorLine();
	setSelection(line, 0, line, lineLength(line));

	replaceSelectedText(text + "\n");
}

int SciCodeEditor::cursorLine() const
{
	int line = 0;
	int index = 0;
	getCursorPosition(&line, &index);

	return line;
}

void SciCodeEditor::format()
{
	int line = 0;
	int indent = 0;
	QString finalText{};

	assert(qstrlen(m_lexer->blockStart()) == 1);
	assert(qstrlen(m_lexer->blockEnd()) == 1);

	char blockStart = m_lexer->blockStart()[0];
	char blockEnd = m_lexer->blockEnd()[0];

	while (line < lines())
	{
		QString lineText = text(line).simplified();

		/*若第一个非空字符为块终结符，则减少缩进*/
		if (lineText.size()>0 && lineText.at(0) == blockEnd)
		{
			indent -= indentationWidth();
		}

		/*添加缩进字符*/
		for (int i = 0; i < indent; i++)
		{
			lineText.insert(0, ' ');
		}
		if (line < lines() - 1)
		{
			lineText.append('\n');	/*添加行尾*/
		}

		finalText += lineText;	/*记录新行*/

		/*设置下一行缩进*/
		for (auto c : lineText)
		{
			if (c == blockStart)
			{
				indent += indentationWidth();
			}
			else if (c == blockEnd)
			{
				indent -= indentationWidth();
			}

			if (indent < 0)
			{
				indent = 0;
			}
		}

		++line;
	}

	setText(finalText);

	updateMargin();
}

void SciCodeEditor::initAutoCompletionSetting()
{
	this->setAutoCompletionSource(QsciScintilla::AcsAPIs);	/*设置自动完成仅限于从Api加入的单词*/
	this->setAutoCompletionThreshold(1);	/*敲入一个字母后弹出自动完成列表*/
}

void SciCodeEditor::initBraceMatching()
{
	this->setBraceMatching(QsciScintilla::SloppyBraceMatch);	/*大致括号匹配*/
}

void SciCodeEditor::initCaretSetting()
{
	this->setCaretWidth(2);	/*插入符号宽度*/
	this->setCaretLineVisible(true);	/*插入符号行*/
	this->setCaretLineBackgroundColor(QColor(100, 100, 100, 100));	/*插入符号行背景色*/
}

void SciCodeEditor::initIndentSetting()
{
	this->setAutoIndent(true);	/*自动缩进*/
	this->setIndentationWidth(4);	/*自动缩进4字符*/
}

void SciCodeEditor::initFoldingSetting()
{
	this->setFolding(QsciScintilla::CircledFoldStyle, FOLD_MARGIN);	/*设置折叠显示方式*/
	/*折叠标签样式*/
	this->markerDefine(QPixmap(plus_xpm), SC_MARKNUM_FOLDER);
	this->markerDefine(QPixmap(minus_xpm), SC_MARKNUM_FOLDEROPEN);
	this->markerDefine(QPixmap(plus_xpm), SC_MARKNUM_FOLDEREND);
	this->markerDefine(QPixmap(minus_xpm), SC_MARKNUM_FOLDEROPENMID);
}

void SciCodeEditor::initMarginSetting()
{
	/*设置标志边界*/
	this->setMarginType(FLAGS_MARGIN, QsciScintilla::SymbolMargin);	/*设置边界类型*/
	this->setMarginWidth(FLAGS_MARGIN, 20);	/*设置边界宽度*/
	this->setMarginMarkerMask(FLAGS_MARGIN, (1 << EXECUTE_MARKER) + (1 << WRONG_MARKER));	/*设置标记*/
	this->markerDefine(QsciScintilla::RightArrow, EXECUTE_MARKER);	/*设置执行代码行标记样式*/
	this->setMarkerBackgroundColor(QColor("#0000ff"), EXECUTE_MARKER);	/*设置执行代码行标记颜色*/

	/*设置错误行标记*/
	this->markerDefine(QPixmap(":/CodeEditor/Resources/wrong_icon.png").scaled(marginWidth(FLAGS_MARGIN), textHeight(0),
		Qt::KeepAspectRatio), WRONG_MARKER);

	/*设置行号边界*/
	this->setMarginType(LINE_NUMBER_MARGIN, QsciScintilla::NumberMargin);	/*设置行区域*/
	this->setMarginLineNumbers(LINE_NUMBER_MARGIN, true);	/*显示行数*/
	this->setMarginWidth(LINE_NUMBER_MARGIN, "   ");	/*行边界宽度*/

	connect(this, &QsciScintilla::linesChanged, [this]{
		this->setMarginWidth(LINE_NUMBER_MARGIN, QString::number(lines()) + " ");
	});

}

void SciCodeEditor::initIndicator()
{
	indicatorDefine(FullBoxIndicator, SEARCH_INDICATOR);
	setIndicatorForegroundColor(QColor::fromRgb(0xFF, 0xE1, 0x53, 100), SEARCH_INDICATOR);
}

void SciCodeEditor::updateMargin()
{
	highlightPCLine(m_executeLine);
}

void SciCodeEditor::updateKeywords(const QStringList& keywords)
{
	for (auto word : keywords)
	{
		m_apis->add(word);
	}

	m_lexer->updateKeywords(keywords);
}

void SciCodeEditor::insertTextBeforeLine(const QString& text)
{
	insertAt(text + "\n", cursorLine(), 0);
}

SciCodeEditor::Range::Range(int lineFrom, int indexFrom, int lineTo, int indexTo)
	:lineFrom(lineFrom)
	, indexFrom(indexFrom)
	, lineTo(lineTo)
	, indexTo(indexTo)
{
}

