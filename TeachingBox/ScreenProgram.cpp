﻿#include "stdafx.h"
#include "ScreenProgram.h"
#include "QBoxLayout"
#include "CodeEditor.h"
#include "Button.h"
#include "ButtonGroup.h"



ScreenProgram::ScreenProgram(QWidget* parent)
	:ScreenMainParent(parent)
	, m_codeEditor(CodeEditor::GetInstance())
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

	/*高级功能*/
	, m_btnKeyboard(new Button(this))
	, m_btnSubProgram(new Button(this))
	, m_btnFormat(new Button(this))
	, m_btnSearch(new Button(this))
	, m_btnNote(new Button(this))
	, m_btnInvalidate(new Button(this))
{
	Init();
}

ScreenProgram::~ScreenProgram()
{
}

void ScreenProgram::SlotNoAddvanceButtonClicked()
{
	m_btnGroupAddvance->show();
}

void ScreenProgram::SlotOnEditButtonClicked()
{
	m_btnGroupEdit->show();
}

void ScreenProgram::Init()
{
	InitSignalSlot();

	InitButtonGroup();

	UpdateText();
}

void ScreenProgram::InitSignalSlot()
{
	connect(m_btnAddvance, SIGNAL(clicked()), this, SLOT(SlotNoAddvanceButtonClicked()));
	connect(m_btnEdit, SIGNAL(clicked()), this, SLOT(SlotOnEditButtonClicked()));
}

QList<QPushButton*> ScreenProgram::GetButtonList()
{
	QList<QPushButton*> btnList;

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
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(m_codeEditor);

	return layout;
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
	m_btnSubProgram->setText(tr("SubProgram"));
	m_btnFormat->setText(tr("Format"));
	m_btnSearch->setText(tr("Search"));
	m_btnNote->setText(tr("Note"));
	m_btnInvalidate->setText(tr("Invalidate"));

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
	QList<Button*> btnGroupEdit;
	btnGroupEdit.append(m_btnSelectAll);
	btnGroupEdit.append(m_btnCut);
	btnGroupEdit.append(m_btnCopy);
	btnGroupEdit.append(m_btnPaste);
	btnGroupEdit.append(m_btnDelete);
	btnGroupEdit.append(m_btnUndo);
	btnGroupEdit.append(m_btnRedo);

	m_btnGroupEdit = new ButtonGroup(btnGroupEdit, m_btnEdit);
}

void ScreenProgram::InitAddvanceGroup()
{
	QList<Button*> btnGroupAddvance;
	btnGroupAddvance.append(m_btnKeyboard);
	btnGroupAddvance.append(m_btnSubProgram);
	btnGroupAddvance.append(m_btnFormat);
	btnGroupAddvance.append(m_btnSearch);
	btnGroupAddvance.append(m_btnNote);
	btnGroupAddvance.append(m_btnInvalidate);

	m_btnGroupAddvance = new ButtonGroup(btnGroupAddvance, m_btnAddvance);
}