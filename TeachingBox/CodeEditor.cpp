﻿#include "stdafx.h"
#include "CodeEditor.h"
#include "Context.h"
#include "ProjectManager.h"
#include <assert.h>


namespace{
	LineNumberArea::LineNumberArea(CodeEditor *editor)
		: QWidget(editor)
		, codeEditor(editor)
	{
	}

	QSize LineNumberArea::sizeHint() const
	{
		return QSize(codeEditor->GetLineNumberAreaWidth(), 0);
	}

	void LineNumberArea::paintEvent(QPaintEvent *event)
	{
		codeEditor->PaintLineNumberArea(event);
	}

	const QColor LineHighlighter::COLOR_PC{ QColor(Qt::blue).lighter(160) };	

	const QColor LineHighlighter::COLOR_WRONG{ QColor(Qt::red).light(160) };

	const QColor LineHighlighter::COLOR_EDIT{ QColor(Qt::yellow).light(160) };
}

CodeEditor* CodeEditor::GetInstance()
{
	return SingleTon<CodeEditor>::GetInstance();
}

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
	m_lineNumberArea = new LineNumberArea(this);

	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(SlotUpdateCodeAreaWidth(int)));
	connect(this, SIGNAL(updateRequest(QRect, int)), this, SLOT(SlotUpdateLineNumberArea(QRect, int)));
	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(SlotHighlightCurrentLine()));

	SlotUpdateCodeAreaWidth(0);
	SlotHighlightCurrentLine();

	this->setCursorWidth(0);
}

CodeEditor::~CodeEditor()
{
}

/*返回左侧区域宽度*/
int CodeEditor::GetLineNumberAreaWidth()
{
	int digits = 1;
	int max = qMax(1, blockCount());
	while (max >= 10)
	{
		max /= 10;
		++digits;
	}

	/*宽度取决于行数的位数*/
	int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

	return space;
}

void CodeEditor::ClearWrongLine()
{
	HighlightWrongLine(0);
}

int CodeEditor::GetPCLineNumber()
{
	return m_lineHighlighter.pcLine.lineNumber+1;
}

void CodeEditor::HighlightPCLine(const QString& program, int lineNumber)
{
	UpdateTextFromProgram(program);

	HighlightPCLine(lineNumber);
}

void CodeEditor::HighlightPCLine()
{
	HighlightPCLine(textCursor().blockNumber()+1);
}

void CodeEditor::HighlightPCLine(int lineNumber)
{
	Context::interpreterContext.SetLineNumber(lineNumber);
	m_lineHighlighter.pcLine.lineNumber = lineNumber-1;
	HighlightAllLines();
}

void CodeEditor::UpdateTextFromProgram(const QString &program)
{
	if (program != Context::projectContext.ProgramOpened())
	{
		auto stringList = program.split(".");
		assert(stringList.size() == 2);

		if (stringList.size() != 2)
		{
			return;
		}

		auto project = stringList.at(0);
		auto file = stringList.at(1);

		ProjectManager projectManager;

		setPlainText(projectManager.GetFileText(project, file));
		Context::projectContext.ProgramOpened(program);
	}
}

void CodeEditor::HighlightWrongLine(const int lineNumber)
{
	m_lineHighlighter.wrongLine.lineNumber = lineNumber-1;
	HighlightAllLines();
}

void CodeEditor::HighlightWrongLine(const QString& program, const int lineNumber)
{
	UpdateTextFromProgram(program);

	HighlightWrongLine(lineNumber);
}

void CodeEditor::HighLightEditLine(const int lineNumber)
{
	m_lineHighlighter.editLine.lineNumber = lineNumber;
	HighlightAllLines();
}

void CodeEditor::HighlightAllLines()
{
	QList<QTextEdit::ExtraSelection> selections;
	AddSelection(selections, m_lineHighlighter.editLine);
	AddSelection(selections, m_lineHighlighter.pcLine);
	AddSelection(selections, m_lineHighlighter.wrongLine);

	setExtraSelections(selections);
}

void CodeEditor::AddSelection(QList<QTextEdit::ExtraSelection>& selections, const LightLine lightLine)
{
	if (lightLine.lineNumber==-1)
	{
		return;
	}
	selections.append(GetSelection(lightLine.lineNumber, lightLine.color));
}

QTextEdit::ExtraSelection CodeEditor::GetSelection(int lineNumber, const QColor& color)
{
	QTextBlock block = this->document()->findBlockByLineNumber(lineNumber);
	QTextCursor cursor(block);

	QTextEdit::ExtraSelection selection;
	selection.format.setBackground(color);
	selection.format.setProperty(QTextFormat::FullWidthSelection, true);
	selection.cursor = cursor;
	selection.cursor.clearSelection();

	return selection;
}

//void CodeEditor::ClearWrongLine()
//{
//	m_extraSelections.clear();
//
//	m_wrongSelection.format.clearBackground();
//	m_wrongSelection.format.clearProperty(QTextFormat::FullWidthSelection);
//
//	m_extraSelections.append(m_selectSelection);
//	m_extraSelections.append(m_pcSelection);
//	m_extraSelections.append(m_wrongSelection);
//
//	setExtraSelections(m_extraSelections);
//}

/*更新右侧区域宽度*/
void CodeEditor::SlotUpdateCodeAreaWidth(int /* newBlockCount */)
{
	setViewportMargins(GetLineNumberAreaWidth(), 0, 0, 0);
}

/*更新左侧区域*/
void CodeEditor::SlotUpdateLineNumberArea(const QRect &rect, int dy)
{
	if (dy)
	{
		m_lineNumberArea->scroll(0, dy);
	}
	else
	{
		/*通过调用update函数，而非直接调用PaintLineNumberArea函数，是为了保证能够实时更新*/
		m_lineNumberArea->update(0, rect.y(), m_lineNumberArea->width(), rect.height());
	}
	if (rect.contains(viewport()->rect()))
	{
		SlotUpdateCodeAreaWidth(0);
	}
}

/*行数控件大小随编辑器大小变化*/
void CodeEditor::resizeEvent(QResizeEvent *e)
{
	QPlainTextEdit::resizeEvent(e);

	QRect cr = contentsRect();
	m_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), GetLineNumberAreaWidth(), cr.height()));
}

void CodeEditor::showEvent(QShowEvent *)
{
	//m_pcSelection.format.clearBackground();
	//m_pcSelection.format.clearProperty(QTextFormat::FullWidthSelection);
	//m_wrongSelection.format.clearBackground();
	//m_wrongSelection.format.clearProperty(QTextFormat::FullWidthSelection);
}

/*高亮显示某行*/
void CodeEditor::SlotHighlightCurrentLine()
{
	HighLightEditLine(textCursor().blockNumber());
}

//int CodeEditor::GetPCLineNumber()
//{
//	return m_pcSelection.cursor.blockNumber() + 1;
//}

/*************************************************
//  Function: 		PaintLineNumberArea
//  Description: 	绘制左侧行号区域
//  Calls:
//  Called By: 		CLineNumberArea::paintEvent
//  Parameter:      QPaintEvent *event
//  Return: 		void
//  Others: 		通过CLineNumberArea类的paintEvent函数来调用本函数，
以保证能够实时更新该行数
*************************************************/
void CodeEditor::PaintLineNumberArea(QPaintEvent *event)
{
	QPainter painter(m_lineNumberArea);
	painter.fillRect(event->rect(), Qt::lightGray);	/*行数背景颜色*/
	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();	/*当前行(从0开始)*/


	int top = (int)blockBoundingGeometry(block).translated(contentOffset()).top() + fontMetrics().descent();/*绘制区域的顶部*/
	int bottom = top + (int)blockBoundingRect(block).height();	/*绘制区域的底部*/

	/*绘制可见区域*/
	while (block.isValid() && top <= event->rect().bottom())
	{
		if (block.isVisible() && bottom >= event->rect().top())
		{
			QString number = QString::number(blockNumber + 1);
			painter.setPen(Qt::black);	/*行号颜色*/
			painter.drawText(0, top, m_lineNumberArea->width(), fontMetrics().height(),
				Qt::AlignCenter, number);
		}

		block = block.next();
		top = bottom;
		bottom = top + (int)blockBoundingRect(block).height();
		++blockNumber;
	}
}

QString CodeEditor::CurrentLineText()
{
	/*获取光标所在行文本*/
	QTextCursor cursor = textCursor();
	cursor.select(QTextCursor::LineUnderCursor);
	return cursor.selectedText();
}

void CodeEditor::InsertTextBeforeLine(const QString& text)
{
	moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
	insertPlainText(text + "\n");
	++m_textChangeTime;
}
//
//void CodeEditor::InsertTextBeforeLineUnsafely(const QString& strText)
//{
//	_InsertTextBeforeLine(strText);
//	FormatCurrentText();
//}

//
//void CodeEditor::_DeleteCurrentLine()
//{
//	QTextCursor currentCursor = this->textCursor();
//	currentCursor.select(QTextCursor::BlockUnderCursor);
//	currentCursor.removeSelectedText();
//	++m_textChangeTime;
//	if (currentCursor.atStart())
//	{
//		currentCursor.deleteChar();
//		++m_textChangeTime;
//	}
//}
//
void CodeEditor::UpdateCurrentLine(const QString& text)
{
	QTextCursor textCursor = this->textCursor();
	textCursor.select(QTextCursor::LineUnderCursor);
	textCursor.removeSelectedText();
	textCursor.insertText(text);
}
//
//void CodeEditor::_InsertTextBeforeLine(const QString& text)
//{
//	moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
//	insertPlainText(text + "\n");
//	++m_textChangeTime;
//}
//
//void CodeEditor::OperatorText(OperatorType operatorType, const QString& text)
//{
//	int lastLineNumber = textCursor().blockNumber();
//
//	switch (operatorType)
//	{
//	case CodeEditor::UPDATE_LINE:
//	{
//		_UpdateCurrentLine(text);
//	}
//	break;
//	case CodeEditor::DELETE_LINE:
//	{
//		_DeleteCurrentLine();
//	}
//	break;
//	case CodeEditor::INSERT_LINE:
//	{
//		_InsertTextBeforeLine(text);
//	}
//	break;
//	default:
//		break;
//	}
//
//	DealText();
//	SaveFile();
//
//	while (lastLineNumber-- > 0)
//	{
//		this->moveCursor(QTextCursor::Down, QTextCursor::MoveAnchor);
//	}
//	SlotHighlightCurrentLine();
//}
//
//void CodeEditor::SaveFile()
//{
//	/*CFileManager fileManager;
//	fileManager.SetFileText(toPlainText(), CScreenProject::GetInstance()->GetOpenedFilePath());*/
//}

//
//void CodeEditor::DealText()
//{
//	if (ParseText())
//	{
//		FormatText(this->toPlainText());
//	}
//}
//
//void CodeEditor::DeleteCurrentLine()
//{
//	OperatorText(DELETE_LINE);
//}
//
//void CodeEditor::FormatText(const QString& )
//{
//	//CTextFormat textFormat;
//	//QString strNewText;
//	//textFormat.FormatText(text, strNewText);
//	//QPlainTextEdit::setPlainText(strNewText);
//}
//
//void CodeEditor::FormatCurrentText()
//{
//	FormatText(toPlainText());
//}
//
//bool CodeEditor::ParseText()
//{
//	//CInterpreterManager* interpreterManager = CInterpreterManager::GetInstance();
//
//	///*检查语法错误并生成语法树*/
//	//try
//	//{
//	//	interpreterManager->AddProgramNode(CScreenProject::GetInstance()->GetOpenedFileName().toStdString(), this->toPlainText().toStdString());
//	//}
//	//catch (CExceptionInterpreter& e)
//	//{
//	//	while (m_textChangeTime>0)
//	//	{
//	//		this->undo();
//	//		--m_textChangeTime;
//	//	}
//
//	//	std::string strWarning;
//	//	CInterpreterManager::GetInstance()->GetWarningInfo(e, strWarning);
//	//	CWarningManager::GetInstance()->Warning(this, QString::fromStdString(strWarning));
//	//	return false;
//	//}
//
//	//return true;
//	return false;
//}


//void CodeEditor::setPlainText(const QString &text)
//{
//	FormatText(text);
//}

//void CCodeEditor::SetText(const QString& text)
//{
//	setPlainText(text);
//	//ParseText();
//}


//void CCodeEditor::SlotFormatText()
//{
//	FormatText();
//}

//void CodeEditor::UpdateLineText(const QString& strNewText)
//{
//	OperatorText(UPDATE_LINE, strNewText);
//}

