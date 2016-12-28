#include "stdafx.h"
#include "ScreenVariate.h"
#include "QTreeWidget"
#include "ButtonGroup.h"
#include "DialogNewVariate.h"
#include "WarningManager.h"
#include "TScope.h"
#include "Context.h"
#include "TVariateManager.h"
#include "QMessageBox"
#include "Button.h"
#include "VariateManagerWithHorizonHeader.h"
#include "TreeWidgetItemWithSymbol.h"
#include <assert.h>
#include "TVariate.h"
#include "TPosition.h"
#include "RemoteFeedbackController.h"
#include "RemoteManager.h"

ScreenVariate::ScreenVariate(QWidget* parent /*= 0*/)
	:ScreenMainParent(parent)
	, m_treeWidget(new QTreeWidget(this))
	, m_btnVariate(new Button(this))
	, m_btnTeach (new Button(this))
	, m_btnCheck(new Button(this))
	, m_btnClearUnused (new Button(this))
	, m_btnSave(new Button(this))
{
	Init();
}

ScreenVariate::~ScreenVariate()
{

}

void ScreenVariate::SlotOnDeleteVariateButtonClicked()
{
	auto item = m_treeWidget->currentItem();
	if (item==nullptr || item->parent()==nullptr)
	{
		WarningManager::Warning(this, tr("Please select a variate"));
		return;
	}

	if (item->parent()->parent()!=nullptr)
	{
		item = item->parent();
	}

	auto parentItem = item->parent();
	QString scope = parentItem->text(0);
	QString name = item->text(1);

	switch (QMessageBox::warning(this, tr("Warning"), tr("Delete variate?") + "\n"+ name, QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok))
	{
	case QMessageBox::Ok:{
		TVariateManager::GetInstance()->DeleteVariate(scope, name);

		parentItem->removeChild(item);
		delete item;
	}break;
	case QMessageBox::Cancel:{

	}break;
	default:
		break;
	}
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

void ScreenVariate::SlotOnTeachButtonClicked()
{
	//WarningManager::GetInstance()->Warning(this, QStringLiteral("未实现"));
	RemoteManager::GetInstance()->SendCommandToGetPosition();
}

QList<QPushButton*> ScreenVariate::GetButtonList()
{
	QList<QPushButton*> btnList;
	btnList.push_back(m_btnVariate);
	btnList.push_back(m_btnTeach);
	btnList.push_back(m_btnClearUnused);
	btnList.push_back(m_btnCheck);
	btnList.push_back(m_btnSave);

	return btnList;
}

QLayout* ScreenVariate::GetMainLayout()
{
	QHBoxLayout* layout=new QHBoxLayout(this);
	layout->addWidget(m_treeWidget);

	return layout;
}

void ScreenVariate::showEvent(QShowEvent *e)
{
	ScreenMainParent::showEvent(e);
	InitTreeWidget();
}



void ScreenVariate::OnReseivePosition(const tAxesAllPositions& position)
{
	if (typeid(*m_treeWidget->currentItem())!=typeid(TreeWidgetItemWithSymbol))
	{
		return;
	}
	auto item = dynamic_cast<TreeWidgetItemWithSymbol*>(m_treeWidget->currentItem());
	if (item->GetSymbol().GetTypeName()!=TPosition::TypeName())
	{
		return;
	}

	auto variate = VariateManagerWithHorizonHeader::GetInstance()->GetVariate(m_treeWidget, item);
	assert(typeid(*variate) == typeid(TPosition));
	std::dynamic_pointer_cast<TPosition>(variate)->SetValue(position);
	VariateManagerWithHorizonHeader::GetInstance()->UpdateWidget(variate, m_treeWidget, item);
	TVariateManager::GetInstance()->UpdateVariate(variate);
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
	InitButtonWidget();
	InitSignalSlot();

	m_btnTeach->setEnabled(false);

	UpdateText();
}

void ScreenVariate::InitTreeWidget()
{
	m_treeWidget->clear();
	m_treeWidget->setColumnCount(2);
	m_treeWidget->header()->setSectionResizeMode(QHeaderView::Stretch);	//平均分布各列

	QStringList scopes = Context::projectContext.AllCurrentScopes();

	for (auto scope : scopes)
	{
		auto treeItem = new QTreeWidgetItem(QStringList{ scope });
		m_treeWidget->addTopLevelItem(treeItem);

		auto variates = TVariateManager::GetInstance()->GetVariatesFromScope(scope);
		for (auto variate : variates)
		{
			VariateManagerWithHorizonHeader::GetInstance()->InsertVariate(std::shared_ptr<TVariate>(variate->Clone()), m_treeWidget, treeItem);
		}
	}
	connect(m_treeWidget, &QTreeWidget::currentItemChanged, [this](QTreeWidgetItem *current, QTreeWidgetItem *){
		if (current==nullptr)
		{
			return;
		}
		if (typeid(*current) == typeid(TreeWidgetItemWithSymbol))
		{
			if (dynamic_cast<TreeWidgetItemWithSymbol*>(current)->GetSymbol().GetTypeName() == TPosition::TypeName()){
				m_btnTeach->setEnabled(true);
				RemoteFeedbackController::GetInstance()->AddListener(this);
			}
			else{
				m_btnTeach->setEnabled(false);
				RemoteFeedbackController::GetInstance()->DeleteListener(this);
			}
		}
	});
}

void ScreenVariate::InitButtonWidget()
{
	m_btnCopy = new Button(this);
	m_btnCut = new Button(this);
	m_btnPaste = new Button(this);
	m_btnRename = new Button(this);
	m_btnNew = new Button(this);
	m_btnDelete = new Button(this);

	QList<QPushButton*> btnList;
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
	connect(m_btnDelete, SIGNAL(clicked()), this, SLOT(SlotOnDeleteVariateButtonClicked()));
	connect(m_btnTeach, &QPushButton::clicked, this, &ScreenVariate::SlotOnTeachButtonClicked);
	connect(m_btnSave, &QPushButton::clicked, [this]{
		for (int i = 0; i < m_treeWidget->topLevelItemCount(); ++i)
		{
			auto scopeItem = m_treeWidget->topLevelItem(i);

			for (int j = 0; j < scopeItem->childCount(); ++j)
			{
				auto variateItem = scopeItem->child(j);
				assert(typeid(*variateItem) == typeid(TreeWidgetItemWithSymbol));
				auto item = dynamic_cast<TreeWidgetItemWithSymbol*>(variateItem);
				if (item->IsSave())
				{
					TVariateManager::GetInstance()->UpdateVariate(VariateManagerWithHorizonHeader::GetInstance()->GetVariate(m_treeWidget, variateItem));
				}
			}
		}
	});
}

void ScreenVariate::UpdateText()
{
	m_btnVariate->setText(tr("Variate"));
	m_btnTeach->setText(tr("Teach"));
	m_btnClearUnused->setText(tr("Clear Unused"));
	m_btnCheck->setText(tr("Check"));
	m_btnSave->setText(tr("Save"));

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
	VariateManagerWithHorizonHeader::GetInstance()->InsertVariate(std::shared_ptr<TVariate>(variate.Clone()), m_treeWidget, FindScopeItem(variate.GetScope()));
	//variate.WriteToTreeWidgetItem(FindScopeItem(variate.GetScope()), m_treeWidget);
}
