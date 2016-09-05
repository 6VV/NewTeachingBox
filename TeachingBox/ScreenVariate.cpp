#include "stdafx.h"
#include "ScreenVariate.h"
#include "QTreeWidget"
#include "ButtonGroup.h"
#include "DialogNewVariate.h"
#include "WarningManager.h"
#include "TScope.h"
#include "Context.h"
#include "TVariateManager.h"

ScreenVariate::ScreenVariate(QWidget* parent /*= 0*/)
	:ScreenMainParent(parent)
	, m_treeWidget(new QTreeWidget(this))
	, m_btnVariate(new Button(this))
	, m_btnTeach (new Button(this))
	, m_btnCheck(new Button(this))
	, m_btnClearUnused (new Button(this))

{
	Init();
}

ScreenVariate::~ScreenVariate()
{

}

void ScreenVariate::SlotOnVariateButtonClicked()
{
	m_btnGroupVariate->show();
}

void ScreenVariate::SlotOnNewVariateButtonClicked()
{
	auto item = m_treeWidget->currentItem();

	if (item==nullptr)
	{
		WarningManager::Warning(this, tr("Please select a scope"));
		return;
	}
	
	auto scopeItem = item;
	while (scopeItem->parent()!=nullptr)
	{
		scopeItem = scopeItem->parent();
	}

	(new VariateWidget::DialogNewVariate(scopeItem->text(0),this,this))->show();
}

QList<QPushButton*> ScreenVariate::GetButtonList()
{
	QList<QPushButton*> btnList;
	btnList.push_back(m_btnVariate);
	btnList.push_back(m_btnTeach);
	btnList.push_back(m_btnClearUnused);
	btnList.push_back(m_btnCheck);

	return btnList;
}

QLayout* ScreenVariate::GetMainLayout()
{
	QHBoxLayout* layout=new QHBoxLayout(this);
	layout->addWidget(m_treeWidget);

	return layout;
}

QTreeWidgetItem* ScreenVariate::FindScopeItem(const QString& scope)
{
	for (int i = 0; i < m_treeWidget->topLevelItemCount();++i)
	{
		auto item = m_treeWidget->topLevelItem(i);
		QString text = item->text(0);
		text;
		if (item->text(0)==scope)
		{
			return item;
		}
	}

	return nullptr;
}

void ScreenVariate::Init()
{
	InitTreeWidget();
	InitButtonWidget();
	InitSignalSlot();

	UpdateText();
}

void ScreenVariate::InitTreeWidget()
{
	m_treeWidget->setColumnCount(2);
	m_treeWidget->header()->setSectionResizeMode(QHeaderView::Stretch);	//平均分布各列

	QStringList scopes = Context::sProjectContext.GetScopes();

	for (auto scope:scopes)
	{
		auto treeItem = new QTreeWidgetItem(QStringList{ scope });
		m_treeWidget->addTopLevelItem(treeItem);

		auto variates = TVariateManager::GetInstance()->GetVariatesFromScope(scope);
		for (auto variate:variates)
		{
			variate->ReadTreeWidgetItem(treeItem, m_treeWidget);
		}
	}

	//m_treeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList{ TScope::STR_SCOPE_SYSTEM }));
	//m_treeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList{ TScope::STR_SCOPE_SYNERGIC }));
	//m_treeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList{ TScope::STR_SCOPE_GLOBAL }));
	
}

void ScreenVariate::InitButtonWidget()
{
	m_btnCopy = new Button(this);
	m_btnCut = new Button(this);
	m_btnPaste = new Button(this);
	m_btnRename = new Button(this);
	m_btnNew = new Button(this);
	m_btnDelete = new Button(this);

	QList<Button*> btnList;
	btnList.append(m_btnCopy);
	btnList.append(m_btnCut);
	btnList.append(m_btnPaste);
	btnList.append(m_btnRename);
	btnList.append(m_btnNew);
	btnList.append(m_btnDelete);

	m_btnGroupVariate = new ButtonGroup(btnList, m_btnVariate);
}

void ScreenVariate::InitSignalSlot()
{
	connect(m_btnVariate, SIGNAL(clicked()), this, SLOT(SlotOnVariateButtonClicked()));
	connect(m_btnNew, SIGNAL(clicked()), this, SLOT(SlotOnNewVariateButtonClicked()));
}

void ScreenVariate::UpdateText()
{
	m_btnVariate->setText(tr("Variate"));
	m_btnTeach->setText(tr("Teach"));
	m_btnClearUnused->setText(tr("Clear Unused"));
	m_btnCheck->setText(tr("Check"));

	m_btnCopy->setText(tr("Copy"));
	m_btnCut->setText(tr("Cut"));
	m_btnPaste->setText(tr("Paste"));
	m_btnRename->setText(tr("Rename"));
	m_btnNew->setText(tr("New"));
	m_btnDelete->setText(tr("Delete"));

	QStringList headStrings;
	headStrings.append(tr("Variate"));
	headStrings.append(tr("Value"));
	m_treeWidget->setHeaderLabels(headStrings);
}

void ScreenVariate::OnNewVariate(TVariate& variate)
{
	variate.ReadTreeWidgetItem(FindScopeItem(variate.GetScope()), m_treeWidget);

}
