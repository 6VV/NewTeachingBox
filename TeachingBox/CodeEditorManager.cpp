#include "stdafx.h"
#include "CodeEditorManager.h"
#include "Context.h"
#include <assert.h>
#include "ProjectManager.h"
#include "..\CodeEditor\SciCodeEditor.h"
#include "qevent.h"
#include "MacroManager.h"
#include "TeachingBoxBroadcast.h"
#include "TVariateManager.h"
#include "ScreenManager.h"
#include "TVariate.h"


CodeEditorManager* CodeEditorManager::GetInstance()
{
	static CodeEditorManager manager;
	return &manager;
}

void CodeEditorManager::ClearWrongLine() const
{
	m_codeEditor->clearWrongLine();
}

QString CodeEditorManager::CurrentLineText() const
{
	return m_codeEditor->currentLineText();
}

void CodeEditorManager::Cut() const
{
	m_codeEditor->cut();
}

void CodeEditorManager::Copy() const
{
	m_codeEditor->copy();
}

void CodeEditorManager::Format() const
{
	m_codeEditor->format();
}

QWidget* CodeEditorManager::GetWidget() const
{
	return m_codeEditor;
}

int CodeEditorManager::CursorLine() const
{
	return m_codeEditor->cursorLine();
}

int CodeEditorManager::CursorIndex() const
{
	int line = 0;
	int index = 0;
	m_codeEditor->getCursorPosition(&line, &index);

	return index;
}

void CodeEditorManager::HighlightPCLine(const QString& program, int lineNumber) const
{
	UpdateTextFromProgram(program);

	HighlightPCLine(lineNumber);
}

void CodeEditorManager::HighlightPCLine(int lineNumber) const
{
	Context::interpreterContext.SetPCLine(lineNumber);

	Context::interpreterContext.SetProgramExecuting(Context::projectContext.ProgramOpened());
	m_codeEditor->highlightPCLine(lineNumber);
}

void CodeEditorManager::HighlightCurrentPCLine() const
{
	HighlightPCLine(m_codeEditor->cursorLine()+1);
}

void CodeEditorManager::HighlightWrongLine(const QString& program, const int lineNumber) const
{
	UpdateTextFromProgram(program);

	m_codeEditor->highlightWrongLine(lineNumber);
}

void CodeEditorManager::Paste() const
{
	m_codeEditor->paste();
}

void CodeEditorManager::Redo() const
{
	m_codeEditor->redo();
}

void CodeEditorManager::SetText(const QString& text) const
{
	m_codeEditor->setText(text);
}

void CodeEditorManager::Delete() const
{
	m_codeEditor->removeSelectedText();
}

void CodeEditorManager::SelectAll() const
{
	m_codeEditor->selectAll();
}


void CodeEditorManager::Search(const QString& text) const
{
	m_codeEditor->search(text);
}

QString CodeEditorManager::Text() const
{
	return m_codeEditor->text();
}

void CodeEditorManager::UpdateCurrentLine(const QString& text) const
{
	m_codeEditor->updateCurrentLine(text);
}

void CodeEditorManager::UpdateVariateWords(const QStringList& words) const
{
	m_codeEditor->updateVariateWords(words);
}

void CodeEditorManager::Undo() const
{
	m_codeEditor->undo();
}

void CodeEditorManager::InsertTextBeforeLine(const QString& text) const
{
	m_codeEditor->insertTextBeforeLine(text);
}

void CodeEditorManager::Insert(const QString& text, int line, int index) const
{
	m_codeEditor->insertAt(text, line, index);
}

CodeEditorManager::CodeEditorManager()
{
	m_codeEditor = new SciCodeEditor;	/*其生命周期交于其父控件*/

	m_codeEditor->updateKeywords(*(MacroManager::GetInstance()->GetKeywords()));
	m_codeEditor->defineWrongLineMarker(":/new/image/Resources/Image/wrong_icon.png");

	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::OpenProgram, this, &CodeEditorManager::OpenProgram);
}

void CodeEditorManager::UpdateTextFromProgram(const QString &program) const
{
	if (program != Context::projectContext.ProgramOpened())
	{
		auto stringList = program.split(".");
		assert(stringList.size() == 2);

		if (stringList.size() != 2)
		{
			return;
		}

		emit(TeachingBoxBroadcast::GetInstance()->OpenProgram(stringList.at(0), stringList.at(1)));
	}
}

void CodeEditorManager::OpenProgram(const QString& project, const QString& program)
{
	QString nextProgram = project + "." + program;
	QString currentProgram = Context::projectContext.ProgramOpened();

	if (nextProgram == currentProgram)
	{
		ScreenManager::GetInstance()->ChangeScreen(ScreenManager::PROGRAM);
		return;
	}

	ProjectManager projectManager;

	if (!currentProgram.isEmpty())
	{
		projectManager.SaveFile(currentProgram, Text());
	}

	SetText(projectManager.GetFileText(project, program));

	auto variates = TVariateManager::GetInstance()->GetAvailableVariatesScollUp(nextProgram);
	QStringList variateNames{};
	for (auto varaite : variates)
	{
		variateNames.append(varaite->GetName());
	}
	for (auto p : Context::projectContext.Programs())
	{
		variateNames.append(p.split(".").at(1));
	}
	UpdateVariateWords(variateNames);

	Context::projectContext.ProgramOpened(nextProgram);
	ScreenManager::GetInstance()->ChangeScreen(ScreenManager::PROGRAM);

	if (Context::interpreterContext.GetProgramExecuting() == project + "." + program)
	{
		HighlightPCLine(project + "." + program, Context::interpreterContext.GetPCLine());
	}
}

void CodeEditorManager::OnInsert(const QString& text)
{
	int line = 0;
	int index = 0;
	m_codeEditor->getCursorPosition(&line, &index);
	if (line<0 || index<0)
	{
		return;
	}
	m_codeEditor->insert(text);

	for (auto c:text)
	{
		if (c=='\n')
		{
			++line;
			index = 0;
		}
		else
		{
			++index;
		}
	}

	m_codeEditor->setCursorPosition(line, index);
}

