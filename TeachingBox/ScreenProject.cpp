#include "stdafx.h"
#include "ScreenProject.h"
#include "QTreeWidget"
#include "QBoxLayout"
#include "Button.h"
#include "ProjectManager.h"
#include "ButtonGroup.h"



ScreenProject::ScreenProject(QWidget* parent)
	:ScreenMainParent(parent)
	, m_projectManager(new ProjectManager())
	, m_treeWidget(new QTreeWidget(this))
	, m_btnLoad(new Button(this))
	, m_btnOpen(new Button(this))
	, m_btnClose(new Button(this))
	, m_btnInfo(new Button(this))
	, m_btnRefresh(new Button(this))
	, m_btnFile(new Button(this))
	, m_btnNewProgram(new Button(this))
	, m_btnNewProject(new Button(this))
	, m_btnDelete(new Button(this))

{
	Init();
}

ScreenProject::~ScreenProject()
{

}


void ScreenProject::SlotOnButtonDeleteClicked()
{

}

void ScreenProject::SlotOnButtonFileClicked()
{
	m_btnGroupFile->show();
}

void ScreenProject::Init()
{
	m_projectManager->GetAllFiles(m_treeWidget->invisibleRootItem());
	InitButtonGroup();
	InitSignalSlot();

	UpdateText();
}

void ScreenProject::InitButtonGroup()
{
	QList<Button*> btnList;
	btnList.append(m_btnNewProject);
	btnList.append(m_btnNewProgram);
	btnList.append(m_btnDelete); 
	m_btnGroupFile = new ButtonGroup(btnList, m_btnFile);
}

void ScreenProject::InitSignalSlot()
{
	connect(m_btnFile, SIGNAL(clicked()), this, SLOT(SlotOnButtonFileClicked()));
}

QList<QPushButton*> ScreenProject::GetButtonList()
{
	QList<QPushButton*> buttons;
	buttons.append(m_btnLoad);
	buttons.append(m_btnOpen);
	buttons.append(m_btnClose);
	buttons.append(m_btnInfo);
	buttons.append(m_btnRefresh);
	buttons.append(m_btnFile);

	return buttons;
}

QLayout* ScreenProject::GetMainLayout()
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(m_treeWidget);

	return layout;
}

void ScreenProject::UpdateText()
{
	m_treeWidget->setHeaderLabel(tr("Project"));

	m_btnLoad->setText(tr("Load"));
	m_btnOpen->setText(tr("Open"));
	m_btnClose->setText(tr("Close"));
	m_btnInfo->setText(tr("Info"));
	m_btnRefresh->setText(tr("Refresh"));
	m_btnFile->setText(tr("File"));

	m_btnNewProgram->setText(tr("New Program"));
	m_btnNewProject->setText(tr("New Project"));
	m_btnDelete->setText(tr("Delete"));
}
