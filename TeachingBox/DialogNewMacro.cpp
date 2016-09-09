#include "stdafx.h"
#include "DialogNewMacro.h"
#include "QTreeWidget"
#include "Button.h"
#include "QListWidget"
#include "QBoxLayout"
#include "Macro.h"
#include "WarningManager.h"
#include "CodeEditor.h"



DialogNewMacro::DialogNewMacro(QWidget* parent)
	:DialogParent(parent)
	, m_categoryTree(new QTreeWidget(this))
	, m_macroWidget(new QListWidget(this))
	, m_btnConfirm(new Button(this))
	, m_btnCancle(new Button(this))
{
	Init();
}

DialogNewMacro::~DialogNewMacro()
{

}

void DialogNewMacro::SlotOnButtonConfirmClicked()
{
	if (m_macroWidget->currentItem()==nullptr)
	{
		WarningManager::Warning(this, tr("Please select a macro"));
		return;
	}

	QString macro = m_macroWidget->currentItem()->text();

	if (Macro::TEXT_MAP.find(macro)==Macro::TEXT_MAP.end())
	{
		WarningManager::Warning(this, tr("Not Realize"));
		return;
	}
	CodeEditor::GetInstance()->InsertTextBeforeLine(Macro::TEXT_MAP.at(macro));

	delete this;
}

void DialogNewMacro::SlotOnButtonCancleClicked()
{
	delete this;
}

void DialogNewMacro::SlotOnTreeItemClicked(QTreeWidgetItem* item)
{
	if (!IsValidTypeItem(item))
	{
		return;
	}

	m_macroWidget->clear();
	QString type = item->text(0);
	auto macros = Macro::MACRO_MAP.find(type)->second;
	for (auto macro : macros)
	{
		m_macroWidget->addItem(macro);
	}
}

void DialogNewMacro::UpdateText()
{
	this->setWindowTitle(tr("New Macro"));
	m_categoryTree->setHeaderLabel(tr("Category"));

	m_btnConfirm->setText(tr("Confirm"));
	m_btnCancle->setText(tr("Cancle"));
}

QWidget* DialogNewMacro::GetCategoryWidget()
{
	for (auto category: Macro::CATEGORYS)
	{
		QTreeWidgetItem* categoryItem = new QTreeWidgetItem(m_categoryTree, QStringList{ category });
		m_categoryTree->addTopLevelItem(categoryItem);

		auto types = Macro::TYPE_MAP.find(category)->second;
		for (auto type : types)
		{
			categoryItem->addChild(new QTreeWidgetItem(QStringList{ type }));
		}
	}

	return m_categoryTree;
}

void DialogNewMacro::Init()
{
	this->setWindowTitle(tr("New Macro"));

	InitLayout();
	InitSignalSlot();

	UpdateText();
}

void DialogNewMacro::InitLayout()
{
	QVBoxLayout* layout = new QVBoxLayout(this);

	QHBoxLayout* layoutMacro = new QHBoxLayout(this);
	layoutMacro->addWidget(GetCategoryWidget());
	layoutMacro->addWidget(m_macroWidget);

	QHBoxLayout* layoutButton = new QHBoxLayout(this);
	layoutButton->addStretch(0);
	layoutButton->addWidget(m_btnConfirm);
	layoutButton->addStretch(0);
	layoutButton->addWidget(m_btnCancle);
	layoutButton->addStretch(0);

	layout->addLayout(layoutMacro);
	layout->addLayout(layoutButton);
	layout->setStretch(0, 1);
}

void DialogNewMacro::InitSignalSlot()
{
	connect(m_btnConfirm, SIGNAL(clicked()), this, SLOT(SlotOnButtonConfirmClicked()));
	connect(m_btnCancle, SIGNAL(clicked()), this, SLOT(SlotOnButtonCancleClicked()));

	connect(m_categoryTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(SlotOnTreeItemClicked(QTreeWidgetItem*)));
}

inline
bool DialogNewMacro::IsValidTypeItem(QTreeWidgetItem* item)
{
	if (item==nullptr || item->parent()==nullptr)
	{
		return false;
	}

	return true;
}

