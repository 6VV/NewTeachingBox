#include "stdafx.h"
#include "ScreenProject.h"
#include "QTreeWidget"
#include "QBoxLayout"
#include "Button.h"
#include "ProjectManager.h"
#include "ButtonGroup.h"
#include "WarningManager.h"
#include "QInputDialog"
#include "Context.h"
#include "CodeEditor.h"
#include "ScreenManager.h"
#include "InterpreterManager.h"
#include "TInterpreterException.h"


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


void ScreenProject::SlotOnButtonCloseClicked()
{
	if (!IsCurrentItemValidity())
	{
		return;
	}

	QTreeWidgetItem* projectItem = nullptr;
	if (IsCurrentItemProject())
	{
		projectItem = m_treeWidget->currentItem();
	}
	else
	{
		projectItem = m_treeWidget->currentItem()->parent();
	}

	SetLoadState(projectItem, LoadState::UNLOADED);
	Context::projectContext.UnloadProject();
}

void ScreenProject::SlotOnButtonDeleteClicked()
{
	if (!IsCurrentItemValidity())
	{
		return;
	}
	if (IsCurrentItemProject())
	{
		m_projectManager->DeleteProject(m_treeWidget->currentItem()->text(0));
		delete m_treeWidget->takeTopLevelItem(m_treeWidget->currentIndex().row());
	}
	else if (IsCurrentItemProgram())
	{
		auto item = m_treeWidget->currentItem();
		m_projectManager->DeleteProgram(item->parent()->text(0), item->text(0));

		item->parent()->removeChild(item);
		delete item;
	}
}

void ScreenProject::SlotOnButtonFileClicked()
{
	m_btnGroupFile->show();
}

void ScreenProject::SlotOnButtonNewProjectClicked()
{
	/*输入项目名*/
	bool ok;
	QString projectName = QInputDialog::getText(this, tr("New project"), tr("Input project name:"),QLineEdit::Normal,QString(),&ok);
	
	if (!ok)
	{
		return;
	}

	/*若已存在该项目*/
	if (m_projectManager->ExistProject(projectName))
	{
		WarningManager::Warning(this, tr("Already exist ") + projectName);
		return;
	}
	
	/*创建项目 */
	if (m_projectManager->CreateProject(projectName))
	{
		m_treeWidget->addTopLevelItem(new QTreeWidgetItem(m_projectManager->GetStateTexts(projectName)));
	}
}

void ScreenProject::SlotOnButtonNewProgramClicked()
{
	/*若为无效节点*/
	if (!IsCurrentItemValidity())
	{
		return;
	}

	/*输入程序名*/
	bool ok;
	QString program = QInputDialog::getText(this, tr("New program"), tr("Input program name:"), QLineEdit::Normal, QString(), &ok);
	if (!ok)
	{
		return;
	}
	
	/*获取当前项目节点*/
	QTreeWidgetItem* parentItem = nullptr;
	if (IsCurrentItemProject())
	{
		parentItem = m_treeWidget->currentItem();
	}
	else
	{
		parentItem = m_treeWidget->currentItem()->parent();
	}

	/*是否已存在该程序*/
	QString project = parentItem->text(0);
	if (m_projectManager->ExistProgram(project, program))
	{
		WarningManager::Warning(this, tr("Already exist ") + program);
		return;
	}

	/*创建程序，添加节点*/
	if (m_projectManager->CreateProgram(project, program))
	{
		parentItem->addChild(new QTreeWidgetItem(m_projectManager->GetStateTexts(program)));
	}
}

//切换到编辑界面，显示选中文件内容
//若选中的文件已被加载，则设置解释器中下一个执行节点为选中文件对应的程序节点
void ScreenProject::SlotOnButtonOpenClicked()
{
	if (!IsCurrentItemValidity())
	{
		return;
	}

	if (IsCurrentItemProject())
	{
		WarningManager::Warning(this, tr("Please select a program"));
		return;
	}

	QString program = m_treeWidget->currentItem()->text(0);
	QString project = m_treeWidget->currentItem()->parent()->text(0);

	QString nextProgram = project + "." + program;
	QString currentProgram = Context::projectContext.ProgramOpened();

	if (nextProgram==currentProgram)
	{
		ScreenManager::GetInstance()->ChangeScreen(ScreenManager::PROGRAM);
		return;
	}

	auto codeEidtor = CodeEditor::GetInstance();

	if (!currentProgram.isEmpty())
	{
		m_projectManager->SaveFile(currentProgram, codeEidtor->toPlainText());
	}

	codeEidtor->HighlightPCLine(nextProgram, 1);
	//codeEidtor->setPlainText(m_projectManager->GetFileText(project, program));
	//codeEidtor->HighlightPCLine(1);

	//Context::projectContext.SetFileOpened(nextProgram);
	ScreenManager::GetInstance()->ChangeScreen(ScreenManager::PROGRAM);
}

void ScreenProject::SlotOnButtonRefreshClicked()
{
	InitFileTree();
}

void ScreenProject::SlotOnButtonLoadClicked()
{
	if (!IsCurrentItemValidity())
	{
		return;
	}

	QString projectLoaded = Context::projectContext.GetProjectLoaded();
	if (!projectLoaded.isEmpty())
	{
		WarningManager::Warning(this, tr("Already load project") + ":\n" + projectLoaded);
		return;
	}

	QTreeWidgetItem* projectItem = nullptr;
	if (IsCurrentItemProject())
	{
		projectItem = m_treeWidget->currentItem();
		UpdateLoadProjectState(projectItem);
	}
	else
	{
		projectItem = m_treeWidget->currentItem()->parent();

		QString program = m_treeWidget->currentItem()->text(0);
		QString project = projectItem->text(0);

		UpdateLoadProjectState(projectItem);
		SlotOnButtonOpenClicked();
	}
}

void ScreenProject::UpdateLoadProjectState(QTreeWidgetItem* projectItem)
{
	QString project = projectItem->text(0);
	Context::projectContext.SetLoadedProject(project, m_projectManager->GetProjectFiles(project));

	SetLoadState(projectItem, LoadState::LOADED);
}

void ScreenProject::Init()
{
	InitFileTree();
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
	connect(m_btnDelete, SIGNAL(clicked()), this, SLOT(SlotOnButtonDeleteClicked()));
	connect(m_btnNewProject, SIGNAL(clicked()), this, SLOT(SlotOnButtonNewProjectClicked()));
	connect(m_btnNewProgram, SIGNAL(clicked()), this, SLOT(SlotOnButtonNewProgramClicked()));

	connect(m_btnRefresh, SIGNAL(clicked()), this, SLOT(SlotOnButtonRefreshClicked()));
	connect(m_btnLoad, SIGNAL(clicked()), this, SLOT(SlotOnButtonLoadClicked()));
	connect(m_btnOpen, SIGNAL(clicked()), this, SLOT(SlotOnButtonOpenClicked()));
	connect(m_btnClose, SIGNAL(clicked()), this, SLOT(SlotOnButtonCloseClicked()));
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

bool ScreenProject::IsCurrentItemProject()
{
	return m_treeWidget->currentItem() != nullptr && m_treeWidget->currentItem()->parent() == nullptr;
}

bool ScreenProject::IsCurrentItemProgram()
{
	auto currentItem = m_treeWidget->currentItem();
	if (currentItem==nullptr)
	{
		return false;
	}

	if (currentItem->parent() == nullptr)
	{
		return false;
	}

	return true;
}

void ScreenProject::InitFileTree()
{
	m_treeWidget->clear();
	m_treeWidget->header()->setSectionResizeMode(QHeaderView::Stretch);

	m_projectManager->GetAllFiles(m_treeWidget->invisibleRootItem());
}

void ScreenProject::SetLoadState(QTreeWidgetItem* projectItem, LoadState state)
{
	QString stateText{};

	switch (state)
	{
	case ScreenProject::LOADED:
	{
		stateText = tr("Loaded");
	}break;
	case ScreenProject::UNLOADED:
	{
		stateText = "---";
	}break;
	default:
		break;
	}

	projectItem->setText(1, stateText);
	for (auto i = 0; i < projectItem->childCount(); ++i)
	{
		projectItem->child(i)->setText(1, stateText);
	}
}

void ScreenProject::UpdateText()
{
	m_treeWidget->setHeaderLabels(QStringList{ tr("Project"),tr("Setting") });

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

bool ScreenProject::IsCurrentItemValidity()
{
	if (m_treeWidget->currentItem()==nullptr)
	{
		WarningManager::Warning(this, tr("Invalid Item"));
		return false;
	}

	return true;
}
