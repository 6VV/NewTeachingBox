#include "stdafx.h"
#include "MacroWidgetParent.h"
#include "QBoxLayout"
#include "Button.h"
#include "QTreeWidget"
#include "QStringList"
#include "TVariateManager.h"
#include "Context.h"
#include "TPosition.h"



MacroWidgetParent::MacroWidgetParent(const QString& macroText, QWidget* parent /*= nullptr*/)
	:DialogParent(parent)
	, m_treeWidget(new QTreeWidget(this))
	, m_btnConfirm(new Button(this))
	, m_btnCancle(new Button(this))
	, m_variates(std::move(TVariateManager::GetInstance()->GetVariatesScollUp(Context::projectContext.ProgramOpened())))
{
	InitMacroText(macroText);
	InitLayout();
	InitSignalSlot();

	UpdateText();
}

void MacroWidgetParent::UpdateText()
{
	m_treeWidget->setHeaderLabels(QStringList{ tr("Name"), tr("Value") });

	m_btnConfirm->setText(tr("Confirm"));
	m_btnCancle->setText(tr("Cancle"));
}

inline
void MacroWidgetParent::InitMacroText(const QString& macroText)
{
	auto stringList = macroText.split(" ");

	if (stringList.size() == 0)
	{
		return;
	}

	m_macroName = stringList.at(0);

	if (stringList.size() == 1)
	{
		return;
	}

	m_macroParameterText = macroText.right(m_macroName.size()).simplified();
}

inline
void MacroWidgetParent::InitLayout()
{
	QVBoxLayout* layout = new QVBoxLayout(this);

	layout->addWidget(m_treeWidget);
	m_treeWidget->setColumnCount(2);
	m_treeWidget->header()->setSectionResizeMode(QHeaderView::Stretch);

	QHBoxLayout* btnLayout = new QHBoxLayout(this);
	btnLayout->addStretch(1);
	btnLayout->addWidget(m_btnConfirm);
	btnLayout->addWidget(m_btnCancle);

	layout->addLayout(btnLayout);

	layout->setStretch(0, 1);
	layout->setStretch(1, 0);
}

inline
void MacroWidgetParent::InitSignalSlot()
{
	connect(m_btnConfirm, SIGNAL(clicked()), this, SLOT(SlotOnButtonConfirmClicked()));
	connect(m_btnCancle, SIGNAL(clicked()), this, SLOT(SlotOnButtonCancleClicked()));
}

const QStringList MacroWidgetParent::GetVariates(SymbolType type) const
{
	QStringList result;

	for (auto variate : m_variates)
	{
		if (variate->GetType() == type)
		{
			result.append(variate->GetName());
		}
	}

	return result;
}

void MacroWidgetParent::AddPosition(const QString& name)
{
	auto variateComboBox = new QComboBox(m_treeWidget);
	variateComboBox->addItems(GetVariates(SymbolType::TYPE_POSITION));
	variateComboBox->setCurrentText(name);

	auto variate = TVariateManager::GetInstance()->GetVariateSrollUp(Context::projectContext.ProgramOpened(), variateComboBox->currentText());

	if (variate == nullptr)
	{
		TPosition position(Context::projectContext.ProgramOpened(), "", tAxesAllPositions{});
		position.ReadTreeWidgetItem(m_treeWidget->invisibleRootItem(), m_treeWidget);
	}
	else
	{
		variate->ReadTreeWidgetItem(m_treeWidget->invisibleRootItem(), m_treeWidget);
	}

	auto item = m_treeWidget->topLevelItem(m_treeWidget->topLevelItemCount() - 1);

	m_treeWidget->setItemWidget(item, 1, variateComboBox);
}

void MacroWidgetParent::SlotOnButtonConfirmClicked()
{
	OnConfirm();

	delete this;
}

void MacroWidgetParent::SlotOnButtonCancleClicked()
{
	delete this;
}

MacroWidgetParent::~MacroWidgetParent()
{
}
