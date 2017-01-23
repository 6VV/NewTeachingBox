#include "stdafx.h"
#include "ScreenVariate.h"
#include "WarningManager.h"
#include "Button.h"
#include "TVariateManager.h"
#include "RemoteManager.h"
#include "DialogNewVariate.h"
#include "TreeWidgetItemWithSymbol.h"
#include "TPosition.h"
#include "VariateManagerWithHorizonHeader.h"
#include "Context.h"
#include "RemoteFeedbackController.h"
#include "ButtonGroup.h"
#include <assert.h>
#include "TVariateInfo.h"


ScreenVariate::ScreenVariate(QWidget* parent /*= 0*/)
	:ScreenMainParent(parent)
	, m_treeWidget(new QTreeWidget(this))
	, m_variateWidgetManager(VariateManagerWithHorizonHeader::GetInstance())
	, m_btnVariate(new Button(this))
	, m_btnTeach(new Button(this))
	, m_btnCheck(new Button(this))
	, m_btnClearUnused(new Button(this))
	, m_btnSave(new Button(this))
	, m_comboBoxType(new QComboBox(this))
{
	Init();
}

ScreenVariate::~ScreenVariate()
{

}

void ScreenVariate::SlotOnDeleteVariateButtonClicked()
{
	auto item = m_treeWidget->currentItem();
	if (item == nullptr || item->parent() == nullptr)
	{
		WarningManager::Warning(this, tr("Please select a variate"));
		return;
	}

	if (item->parent()->parent() != nullptr)
	{
		item = item->parent();
	}

	auto parentItem = item->parent();
	QString scope = parentItem->text(0);
	QString name = item->text(1);

	switch (QMessageBox::warning(this, tr("Warning"), tr("Delete variate?") + "\n" + name, QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok))
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

	if (item == nullptr)
	{
		WarningManager::Warning(this, tr("Please select a scope"));
		return;
	}

	auto scopeItem = item;
	while (scopeItem->parent() != nullptr)
	{
		scopeItem = scopeItem->parent();
	}

	(new VariateWidget::DialogNewVariate(scopeItem->text(0), this, this))->show();
}

void ScreenVariate::SlotOnTeachButtonClicked()
{
	//WarningManager::GetInstance()->Warning(this, QStringLiteral("未实现"));
	RemoteManager::GetInstance()->SendCommandToGetPosition();
}

QList<QWidget*> ScreenVariate::GetButtonList()
{
	m_comboBoxType->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_comboBoxType->addItem(TYPE_ALL);
	m_comboBoxType->addItems(TVariateInfo::GetAllTypeName());
	connect(m_comboBoxType, &QComboBox::currentTextChanged, [this](const QString& text){
		for (int i = 0; i < m_treeWidget->topLevelItemCount();++i)
		{
			auto scopeItem = m_treeWidget->topLevelItem(i);
			for (int j = 0;j<scopeItem->childCount();++j)
			{
				if (text == TYPE_ALL || text == dynamic_cast<TreeWidgetItemWithSymbol*>(scopeItem->child(j))->GetSymbol().GetTypeName())
				{
					scopeItem->child(j)->setHidden(false);
				}
				else
				{
					scopeItem->child(j)->setHidden(true);
				}
			}
		}
	});

	QList<QWidget*> btnList;
	btnList.push_back(m_btnVariate);
	btnList.push_back(m_btnTeach);
	btnList.push_back(m_btnClearUnused);
	btnList.push_back(m_btnCheck);
	btnList.push_back(m_btnSave);
	btnList.push_back(m_comboBoxType);

	m_btnClearUnused->setEnabled(false);
	m_btnCheck->setEnabled(false);

	return btnList;
}

QLayout* ScreenVariate::GetMainLayout()
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(m_treeWidget);

	return layout;
}

void ScreenVariate::showEvent(QShowEvent *e)
{
	ScreenMainParent::showEvent(e);
	InitTreeWidget();

	m_btnTeach->setEnabled(false);
}

void ScreenVariate::OnReseivePosition(const tAxesAllPositions& position)
{
	if (typeid(*m_treeWidget->currentItem()) != typeid(TreeWidgetItemWithSymbol))
	{
		return;
	}
	auto item = dynamic_cast<TreeWidgetItemWithSymbol*>(m_treeWidget->currentItem());
	if (item->GetSymbol().GetTypeName() != TPosition::TypeName())
	{
		return;
	}
	auto variate = m_variateWidgetManager->GetVariate(m_treeWidget, item);
	//assert(typeid(*variate) == typeid(TPosition));

	std::dynamic_pointer_cast<TComplex>(variate)->SetValues(TPosition::ToCommonValue(position));
	//std::dynamic_pointer_cast<TPosition>(variate)->SetValue(position);
	m_variateWidgetManager->UpdateWidget(variate, m_treeWidget, item);
	TVariateManager::GetInstance()->UpdateVariate(variate);
}

QTreeWidgetItem* ScreenVariate::FindScopeItem(const QString& scope)
{
	for (int i = 0; i < m_treeWidget->topLevelItemCount(); ++i)
	{
		auto item = m_treeWidget->topLevelItem(i);
		QString text = item->text(0);
		text;
		if (item->text(0) == scope)
		{
			return item;
		}
	}

	return nullptr;
}

QString ScreenVariate::GetScope(QTreeWidgetItem* item) const
{
	auto scopeItem = GetScopeItem(item);
	if (scopeItem == nullptr)
	{
		return{};
	}

	return scopeItem->text(0);
}

QTreeWidgetItem* ScreenVariate::GetScopeItem(QTreeWidgetItem* item) const
{
	auto result = item;;
	if (item == nullptr)
	{
		return nullptr;
	}
	if (IsVariateItem(item))
	{
		result = item->parent();
	}
	else if (IsValueItem(item))
	{
		result = item->parent()->parent();
	}

	return result;
}

void ScreenVariate::Init()
{
	InitButtonWidget();
	InitSignalSlot();

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
			m_variateWidgetManager->InsertVariate(std::shared_ptr<TVariate>(variate->Clone()), m_treeWidget, treeItem);
		}
	}

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

	m_btnCopy->setEnabled(false);
	m_btnCut->setEnabled(false);
	m_btnPaste->setEnabled(false);
	m_btnRename->setEnabled(false);
	m_btnNew->setEnabled(false);
	m_btnDelete->setEnabled(false);

	m_btnGroupVariate = new ButtonGroup(btnList, m_btnVariate);
}

void ScreenVariate::InitSignalSlot()
{
	connect(m_treeWidget, &QTreeWidget::currentItemChanged, [this](QTreeWidgetItem *current, QTreeWidgetItem *){
		if (current == nullptr)
		{
			return;
		}
		if (IsVariateItem(current))
		{
			if (GetScope(current->parent())==ProjectContext::ScopeSystem())
			{
				m_btnCopy->setEnabled(false);
				m_btnCut->setEnabled(false);
				m_btnDelete->setEnabled(false);
				m_btnRename->setEnabled(false);
				m_btnTeach->setEnabled(false);
				m_btnNew->setEnabled(false);
				m_btnPaste->setEnabled(false);
			}
			else
			{
				m_btnCopy->setEnabled(true);
				m_btnCut->setEnabled(true);
				m_btnDelete->setEnabled(true);
				m_btnRename->setEnabled(true);

				if (dynamic_cast<TreeWidgetItemWithSymbol*>(current)->GetSymbol().GetTypeName() == TPosition::TypeName()){
					m_btnTeach->setEnabled(true);
					RemoteFeedbackController::GetInstance()->AddListener(this);
				}
				else{
					m_btnTeach->setEnabled(false);
					RemoteFeedbackController::GetInstance()->DeleteListener(this);
				}
			}
			
		}
		else
		{
			m_btnCopy->setEnabled(false);
			m_btnCut->setEnabled(false);
			m_btnDelete->setEnabled(false);
			m_btnRename->setEnabled(false);
			m_btnTeach->setEnabled(false);

			if (current == nullptr || GetScope(current)==ProjectContext::ScopeSystem()){
				m_btnNew->setEnabled(false);
				m_btnPaste->setEnabled(false);
			}
			else{
				m_btnNew->setEnabled(true);
			}
		}
	});
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
					TVariateManager::GetInstance()->UpdateVariate(m_variateWidgetManager->GetVariate(m_treeWidget, variateItem));
				}
			}
		}
	});
	connect(m_btnRename, &QPushButton::clicked, [this]{
		auto item = m_treeWidget->currentItem();
		if (!IsVariateItem(item)){
			return;
		}

		auto variate = m_variateWidgetManager->GetVariate(m_treeWidget, item);

		bool ok = false;
		auto newName = QInputDialog::getText(this, tr("New name"), tr("Input new name:"), QLineEdit::Normal, variate->GetName(), &ok);
		if (!ok || newName == variate->GetName())
		{
			return;
		}

		if (newName.isEmpty())
		{
			WarningManager::Warning(this, tr("name cann't be empty"));
			return;
		}

		auto newVariate = std::shared_ptr<TVariate>(variate->Clone());
		newVariate->SetName(newName);

		TVariateManager::GetInstance()->DeleteVariate(variate->GetScope(), variate->GetName());
		TVariateManager::GetInstance()->AddVariate(newVariate);
		m_variateWidgetManager->UpdateWidget(newVariate, m_treeWidget, item);
	});
	connect(m_btnCopy, &QPushButton::clicked, [this]{
		auto item = m_treeWidget->currentItem();
		if (!IsVariateItem(item))
		{
			return;
		}
		m_pasteInfo.operatorType = PasteInfo::COPY;
		m_pasteInfo.variate = std::shared_ptr<TVariate>(m_variateWidgetManager->GetVariate(m_treeWidget, item)->Clone());
		m_pasteInfo.variate->SetName(m_pasteInfo.variate->GetName() + "_copy");
		m_btnPaste->setEnabled(true);
	});
	connect(m_btnPaste, &QPushButton::clicked, [this]{
		auto item = m_treeWidget->currentItem();
		if (item == nullptr)
		{
			return;
		}

		if (TVariateManager::GetInstance()->GetVariate(GetScope(item), m_pasteInfo.variate->GetName()) != nullptr)
		{
			WarningManager::Warning(this, tr("Already exist:\n") + m_pasteInfo.variate->GetScope() + "." + m_pasteInfo.variate->GetName());
			return;
		}

		if (m_pasteInfo.operatorType == PasteInfo::CUT)
		{
			TVariateManager::GetInstance()->DeleteVariate(m_pasteInfo.variate->GetScope(), m_pasteInfo.variate->GetName());
			for (int i = 0; i < m_treeWidget->topLevelItemCount(); ++i)
			{
				auto scopeItem = m_treeWidget->topLevelItem(i);
				if (GetScope(scopeItem) == m_pasteInfo.variate->GetScope())
				{
					for (int j = 0; j < scopeItem->childCount(); ++j)
					{
						if (m_variateWidgetManager->GetVariate(m_treeWidget, scopeItem->child(j))->GetName() == m_pasteInfo.variate->GetName())
						{
							scopeItem->removeChild(scopeItem->child(j));
							break;
						}
					}
					break;
				}
			}
		}

		m_pasteInfo.variate->SetScope(GetScope(item));
		TVariateManager::GetInstance()->AddVariate(std::shared_ptr<TVariate>(m_pasteInfo.variate->Clone()));
		//m_variateWidgetManager->InsertVariate(m_pasteInfo.variate, m_treeWidget, GetScopeItem(item));
		InsertVariate(m_pasteInfo.variate, GetScopeItem(item));

		m_pasteInfo.variate = nullptr;
		m_btnPaste->setEnabled(false);
	});
	connect(m_btnCut, &QPushButton::clicked, [this]{
		auto item = m_treeWidget->currentItem();
		if (!IsVariateItem(item))
		{
			return;
		}
		m_pasteInfo.operatorType = PasteInfo::CUT;
		m_pasteInfo.variate = std::shared_ptr<TVariate>(m_variateWidgetManager->GetVariate(m_treeWidget, item)->Clone());
		m_btnPaste->setEnabled(true);
	});
}

void ScreenVariate::InsertVariate(std::shared_ptr<TVariate> variate, QTreeWidgetItem* item)
{
	auto variateItem=m_variateWidgetManager->InsertVariate(variate, m_treeWidget, item);
	if (variate->GetTypeName() == m_comboBoxType->currentText() || m_comboBoxType->currentText()==TYPE_ALL)
	{
		variateItem->setHidden(false);
	}
	else
	{
		variateItem->setHidden(true);
	}
}

bool ScreenVariate::IsVariateItem(QTreeWidgetItem* item) const
{
	if (item == nullptr)
	{
		return false;
	}
	return typeid(*item) == typeid(TreeWidgetItemWithSymbol);
}

bool ScreenVariate::IsScopeItem(QTreeWidgetItem* item) const
{
	if (item == nullptr)
	{
		return false;
	}

	return item->parent() == nullptr;
}

bool ScreenVariate::IsValueItem(QTreeWidgetItem* item) const
{
	if (item == nullptr || item->parent() == nullptr || item->parent()->parent() == nullptr)
	{
		return false;
	}

	return true;
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
	//m_variateWidgetManager->InsertVariate(std::shared_ptr<TVariate>(variate.Clone()), m_treeWidget, FindScopeItem(variate.GetScope()));
	InsertVariate(std::shared_ptr<TVariate>(variate.Clone()), FindScopeItem(variate.GetScope()));
}
