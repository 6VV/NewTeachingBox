#include "stdafx.h"
#include "ScreenProgram.h"
#include "QBoxLayout"
#include "CodeEditor.h"
#include "Button.h"
#include "ButtonGroup.h"
#include "DialogNewMacro.h"
#include "Context.h"
#include "MacroWidgetFactory.h"
#include "CodeEditorManager.h"
#include "Keyboard.h"
#include "SimpleKeyboard.h"



ScreenProgram::ScreenProgram(QWidget* parent)
	:ScreenMainParent(parent)
	, m_codeEditor(CodeEditorManager::GetInstance())
	, m_btnModify(new Button(this))
	, m_btnMacro(new Button(this))
	, m_btnNew(new Button(this))
	, m_btnEdit(new Button(this))
	, m_btnSetPC(new Button(this))
	, m_btnAddvance(new Button(this))

	/*编辑功能*/
	, m_btnSelectAll(new Button(this))
	, m_btnCut(new Button(this))
	, m_btnCopy(new Button(this))
	, m_btnPaste(new Button(this))
	, m_btnDelete(new Button(this))
	, m_btnUndo(new Button(this))
	, m_btnRedo(new Button(this))
{
	Init();
}

ScreenProgram::~ScreenProgram()
{
}

void ScreenProgram::SlotOnButtonAddvanceClicked()
{
	m_btnGroupAddvance->show();
}

void ScreenProgram::SlotOnButtonModifyClicked()
{
	auto widget = MacroWidgetFactory::CreateMacroWidget(m_codeEditor->CurrentLineText(), this);

	if (widget==nullptr)
	{
		return;
	}
	widget->show();
}

void ScreenProgram::SlotOnButtonNewClicked()
{
	(new DialogNewMacro(this))->show();
}

void ScreenProgram::SlotOnButtonEditClicked()
{
	m_btnGroupEdit->show();
}

void ScreenProgram::SlotOnButtonSetPCClicked()
{
	m_codeEditor->HighlightCurrentPCLine();

	/*手动设置执行行时，清除记录的函数信息*/
	Context::interpreterContext.ClearFunctionInfo();
}

void ScreenProgram::Init()
{
	InitSignalSlot();

	InitButtonGroup();

	UpdateText();
}

void ScreenProgram::InitSignalSlot()
{
	connect(m_btnAddvance, SIGNAL(clicked()), this, SLOT(SlotOnButtonAddvanceClicked()));
	connect(m_btnModify, SIGNAL(clicked()), this, SLOT(SlotOnButtonModifyClicked()));
	connect(m_btnNew, SIGNAL(clicked()), this, SLOT(SlotOnButtonNewClicked()));
	connect(m_btnEdit, SIGNAL(clicked()), this, SLOT(SlotOnButtonEditClicked()));
	connect(m_btnSetPC, SIGNAL(clicked()), this, SLOT(SlotOnButtonSetPCClicked()));
}

QList<QWidget*> ScreenProgram::GetButtonList()
{
	QList<QWidget*> btnList;

	btnList.append(m_btnModify);
	btnList.append(m_btnMacro);
	btnList.append(m_btnNew);
	btnList.append(m_btnSetPC);
	btnList.append(m_btnEdit);
	btnList.append(m_btnAddvance);

	return btnList;
}

QLayout* ScreenProgram::GetMainLayout()
{
	m_editorLayout = new QVBoxLayout(this);
	m_editorLayout->addWidget(m_codeEditor->GetWidget());

	return m_editorLayout;
}

void ScreenProgram::UpdateText()
{
	m_btnModify->setText(tr("Modify"));
	m_btnMacro->setText(tr("Macro"));
	m_btnNew->setText(tr("New"));
	m_btnSetPC->setText(tr("SetPC"));
	m_btnEdit->setText(tr("Edit"));
	m_btnAddvance->setText(tr("Addvance"));

	/*高级功能*/
	m_btnKeyboard->setText(tr("Keyboard"));
	//m_btnSubProgram->setText(tr("SubProgram"));
	m_btnFormat->setText(tr("Format"));
	m_btnSearch->setText(tr("Search"));
	m_btnNote->setText(tr("Note"));
	//m_btnInvalidate->setText(tr("Invalidate"));

	/*编辑功能*/
	m_btnSelectAll->setText(tr("SelectAll"));
	m_btnCut->setText(tr("Cut"));
	m_btnCopy->setText(tr("Copy"));
	m_btnPaste->setText(tr("Paste"));
	m_btnDelete->setText(tr("Delete"));
	m_btnUndo->setText(tr("Undo"));
	m_btnRedo->setText(tr("Redo"));
}

void ScreenProgram::InitButtonGroup()
{
	InitAddvanceGroup();
	InitEditGroup();
}

void ScreenProgram::InitEditGroup()
{
	QList<QPushButton*> btnGroupEdit;
	btnGroupEdit.append(m_btnSelectAll);
	btnGroupEdit.append(m_btnCut);
	btnGroupEdit.append(m_btnCopy);
	btnGroupEdit.append(m_btnPaste);
	btnGroupEdit.append(m_btnDelete);
	btnGroupEdit.append(m_btnUndo);
	btnGroupEdit.append(m_btnRedo);

	m_btnGroupEdit = new ButtonGroup(btnGroupEdit, m_btnEdit);

	connect(m_btnSelectAll, &QPushButton::clicked, m_codeEditor, &CodeEditorManager::SelectAll);
	connect(m_btnCopy, &QPushButton::clicked, m_codeEditor, &CodeEditorManager::Copy);
	connect(m_btnCut, &QPushButton::clicked, m_codeEditor, &CodeEditorManager::Cut);
	connect(m_btnPaste, &QPushButton::clicked, m_codeEditor, &CodeEditorManager::Paste);
	connect(m_btnDelete, &QPushButton::clicked, m_codeEditor, &CodeEditorManager::Delete);
	connect(m_btnUndo, &QPushButton::clicked, m_codeEditor, &CodeEditorManager::Undo);
	connect(m_btnRedo, &QPushButton::clicked, m_codeEditor, &CodeEditorManager::Redo);
}

/*高级功能*/
void ScreenProgram::InitAddvanceGroup()
{
	m_btnKeyboard=new Button(this);
	m_btnFormat=new Button(this);
	m_btnSearch=new Button(this);
	m_btnNote = new Button(this);

	QList<QPushButton*> btnGroupAddvance;
	btnGroupAddvance.append(m_btnKeyboard);
	btnGroupAddvance.append(m_btnFormat);
	btnGroupAddvance.append(m_btnSearch);
	btnGroupAddvance.append(m_btnNote);

	m_btnGroupAddvance = new ButtonGroup(btnGroupAddvance, m_btnAddvance);

	connect(m_btnFormat, &QPushButton::clicked, m_codeEditor, &CodeEditorManager::Format);
	connect(m_btnSearch, &QPushButton::clicked, [this]{
		bool ok;
		QString text=QInputDialog::getText(this, tr("Search word"), tr("search:"), QLineEdit::Normal, "",&ok);
		if (ok){
			m_codeEditor->Search(text);
		}
	});
	connect(m_btnKeyboard, &QPushButton::clicked, [this]{
		if (m_simpleKeyboard==nullptr)
		{
			m_simpleKeyboard = new SimpleKeyboard(m_codeEditor->GetWidget());
			//m_simpleKeyboard = SimpleKeyboard::GetInstance(m_codeEditor);
			m_editorLayout->addWidget(m_simpleKeyboard);
			m_isKeyboardVisiable = true;
		}
		else
		{
			m_isKeyboardVisiable = !m_isKeyboardVisiable;
			m_simpleKeyboard->setVisible(m_isKeyboardVisiable);
		}
	});
	connect(m_btnNote, &QPushButton::clicked, [this]{
		m_codeEditor->Insert("//", m_codeEditor->CursorLine(), 0);
	});
}

void ScreenProgram::showEvent(QShowEvent *e)
{
	ScreenMainParent::showEvent(e);

	if (!Context::projectContext.IsCurrentFileLoad())
	{
		m_btnSetPC->setEnabled(false);
	}

	m_btnSetPC->setEnabled(true);

}

