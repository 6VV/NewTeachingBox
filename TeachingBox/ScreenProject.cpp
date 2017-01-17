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
#include "TVariateContext.h"
#include "CodeEditorManager.h"
#include "ProjectVariatesXmlManager.h"
#include "QIcon"
#include "TeachingBoxBroadcast.h"
#include "TVariateManager.h"
#include "TVariate.h"

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
	, m_btnExport(new Button(this))
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

	emit(TeachingBoxBroadcast::GetInstance()->LoadProject("", {}));
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
		auto projectItem = new QTreeWidgetItem(m_projectManager->GetStateTexts(projectName));
		projectItem->setIcon(0,QIcon(QPixmap(PROJECT_ICON_PATH)));
		m_treeWidget->addTopLevelItem(projectItem);
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
		auto childItem = new QTreeWidgetItem(m_projectManager->GetStateTexts(program));
		childItem->setIcon(0, QIcon(QPixmap(PROGRAM_ICON_PATH)));
		parentItem->addChild(childItem);

		UpdateLoadProjectState(parentItem);
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

	emit(TeachingBoxBroadcast::GetInstance()->OpenProgram(project,program));
}

void ScreenProject::SlotOnButtonRefreshClicked()
{
	InitFileTree();
	auto list=m_treeWidget->findItems(Context::projectContext.ProjectLoaded(), Qt::MatchFixedString);
	if (list.size()>0)
	{
		SetLoadState(list.at(0), LoadState::LOADED);
	}

}

void ScreenProject::SlotOnButtonLoadClicked()
{
	if (!IsCurrentItemValidity())
	{
		return;
	}

	QString projectLoaded = Context::projectContext.ProjectLoaded();
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

		//QString program = m_treeWidget->currentItem()->text(0);
		//QString project = projectItem->text(0);

		UpdateLoadProjectState(projectItem);	/*更新状态需在打开文件之前，保证文件打开时项目已被加载，各种事件能够被正确响应*/
		SlotOnButtonOpenClicked();
	}

}

void ScreenProject::UpdateLoadProjectState(QTreeWidgetItem* projectItem)
{
	QString project = projectItem->text(0);
	auto programs = std::move(m_projectManager->GetProjectFiles(project));
	Context::projectContext.SetLoadedProject(project, programs);

	/*添加作用域节点，添加节点的主要作用在于防止因部分作用域下不含变量，导致未能在添加变量时将该作用域添加到变量环境中*/
	TVariateContext::GetInstance()->AddScope(project);
	for (auto program:programs)
	{
		TVariateContext::GetInstance()->AddScope(program);	
	}

	SetLoadState(projectItem, LoadState::LOADED);


	for (auto& program : programs)
	{
		program = program.split(".").at(1);
	}
	emit(TeachingBoxBroadcast::GetInstance()->LoadProject(project, programs));
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
	QList<QPushButton*> btnList;
	btnList.append(m_btnNewProject);
	btnList.append(m_btnNewProgram);
	btnList.append(m_btnDelete); 
	btnList.append(m_btnExport);
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
	connect(m_btnExport, &QPushButton::clicked, [this]{
		auto currentItem = m_treeWidget->currentItem();
		if (currentItem==nullptr)
		{
			return;
		}
		while (currentItem->parent()!=nullptr)
		{
			currentItem = currentItem->parent();
		}
		ProjectVariatesXmlManager manager;
		manager.WriteToXml(currentItem->text(0));
	});

	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::OpenProgram, this, &ScreenProject::OpenProgram);
}

QList<QWidget*> ScreenProject::GetButtonList()
{
	QList<QWidget*> buttons;
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

void ScreenProject::OpenProgram(const QString& project, const QString& program)
{
	QString nextProgram = project + "." + program;
	QString currentProgram = Context::projectContext.ProgramOpened();

	if (nextProgram == currentProgram)
	{
		ScreenManager::GetInstance()->ChangeScreen(ScreenManager::PROGRAM);
		return;
	}

	auto codeEidtor = CodeEditorManager::GetInstance();

	if (!currentProgram.isEmpty())
	{
		m_projectManager->SaveFile(currentProgram, codeEidtor->Text());
	}

	ProjectManager projectManager;
	codeEidtor->SetText(projectManager.GetFileText(project, program));

	auto variates = TVariateManager::GetInstance()->GetAvailableVariatesScollUp(nextProgram);
	QStringList variateNames{};
	for (auto varaite:variates)
	{
		variateNames.append(varaite->GetName());
	}
	for (auto p : Context::projectContext.Programs())
	{
		variateNames.append(p.split(".").at(1));
	}
	codeEidtor->UpdateVariateWords(variateNames);

	Context::projectContext.ProgramOpened(nextProgram);
	//codeEidtor->HighlightPCLine(nextProgram, 1);
	ScreenManager::GetInstance()->ChangeScreen(ScreenManager::PROGRAM);
}

void ScreenProject::InitFileTree()
{
	m_treeWidget->clear();
	m_treeWidget->header()->setSectionResizeMode(QHeaderView::Stretch);

	m_projectManager->GetAllFiles(m_treeWidget->invisibleRootItem());

	InitTreeWidgetIcon();

}

void ScreenProject::InitTreeWidgetIcon()
{
	for (int i = 0; i < m_treeWidget->topLevelItemCount(); ++i)
	{
		auto projectItem = m_treeWidget->topLevelItem(i);
		projectItem->setIcon(0, QIcon(QPixmap(PROJECT_ICON_PATH)));
		SetLoadState(projectItem, LoadState::UNLOADED);

		for (int j = 0; j < projectItem->childCount(); ++j)
		{
			projectItem->child(j)->setIcon(0, QIcon(QPixmap(PROGRAM_ICON_PATH)));
			SetLoadState(projectItem->child(j), LoadState::UNLOADED);
		}
	}
}

void ScreenProject::SetLoadState(QTreeWidgetItem* projectItem, LoadState state)
{
	QString iconPath{};

	switch (state)
	{
	case ScreenProject::LOADED:
	{
		iconPath = ":/new/image/Resources/Image/confirm_icon.png";
	}break;
	case ScreenProject::UNLOADED:
	{
		iconPath = ":/new/image/Resources/Image/double_horizon_line_icon.png";
	}break;
	default:
		break;
	}

	projectItem->setIcon(1,QIcon(QPixmap(iconPath)));
	for (auto i = 0; i < projectItem->childCount(); ++i)
	{
		projectItem->child(i)->setIcon(1, QIcon(QPixmap(iconPath)));
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
	m_btnExport->setText(tr("Export"));
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
