#include "stdafx.h"
#include "MacroWidgetParent.h"
#include "Button.h"
#include "TVariate.h"
#include "WarningManager.h"
#include "CodeEditor.h"
#include "VariateWidgetProducer.h"
#include "CodeEditorManager.h"
#include "TVariateFactory.h"


MacroWidgetParent::MacroWidgetParent(const QString& macroText, QWidget* parent /*= nullptr*/)
	:DialogParent(parent)
	, m_treeWidget(new QTreeWidget(this))
	, m_btnConfirm(new Button(this))
	, m_btnCancle(new Button(this))
	, m_variateWidgetProducer(new VariateWidgetProducer())
	, m_variates(std::move(TVariateManager::GetInstance()->GetAvailableVariatesScollUp(Context::projectContext.ProgramOpened())))
{
	InitMacroText(macroText);
	InitLayout();
	InitSignalSlot();

	UpdateText();
}

MacroWidgetParent::~MacroWidgetParent()
{
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

	m_macroParameterList = macroText.right(macroText.size() - m_macroName.size()).simplified().split(",");
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
	connect(m_btnConfirm, &QPushButton::clicked, this, &MacroWidgetParent::SlotOnButtonConfirmClicked);
	connect(m_btnCancle, &QPushButton::clicked, this, &MacroWidgetParent::SlotOnButtonCancleClicked);
}


void MacroWidgetParent::SlotOnButtonConfirmClicked()
{
	for (auto comboBox:m_parameterComboBoxes)
	{
		/*若未存储该变量*/
		if (TVariateManager::GetInstance()->GetVariateSrollUp(Context::projectContext.ProgramOpened(),comboBox ->currentText()) == nullptr)
		{
			bool isNewVariate = false;
			for (auto variate : m_newVariates)
			{
				/*若已新建该变量*/
				if (variate->GetName() == comboBox->currentText())
				{
					isNewVariate = true;

					TVariateManager::GetInstance()->AddVariate(variate);

					break;
				}
			}
			/*若未新建该变量*/
			if (!isNewVariate)
			{
				WarningManager::Warning(this, tr("Operator failed"));
				delete this;
				return;
			}
		}
	}

	for (int i = 0; i < m_treeWidget->topLevelItemCount();++i)
	{
		TVariateManager::GetInstance()->UpdateVariate(VariateManagerWithHorizonHeader::GetInstance()->GetVariate(m_treeWidget, m_treeWidget->topLevelItem(i)));
	}

	OnConfirm();

	delete this;
}

void MacroWidgetParent::SlotOnButtonCancleClicked()
{
	delete this;
}

inline
void MacroWidgetParent::OnConfirm()
{
	QString text = MacroName()+" ";

	for (int i = 0; i < m_parameterComboBoxes.size(); ++i)
	{
		text += m_parameterComboBoxes.at(i)->currentText() + ",";
	}

	CodeEditorManager::GetInstance()->UpdateCurrentLine(text.left(text.size() - 1));
}


void MacroWidgetParent::AddParameter(const QString& typeName, const QString& name)
{
	auto variateComboBox = new QComboBox(m_treeWidget);
	m_variateWidgetProducer->UpdateComboBoxWithSimpleName(typeName, m_variates, variateComboBox);
	m_parameterComboBoxes.append(variateComboBox);

	variateComboBox->setCurrentText(name);

	auto variate = TVariateManager::GetInstance()->GetVariateSrollUp(Context::projectContext.ProgramOpened(), variateComboBox->currentText());

	if (variate == nullptr)
	{
		auto suggestName = m_variateWidgetProducer->GetSuggestName(typeName, m_variates);
		variateComboBox->addItem(QPixmap(VariateWidgetProducer::IMAGE_LOGO_LOCAL), suggestName);
		variate = TVariateFactory::CreateVariate(TSymbol{ Context::projectContext.ProgramOpened(), suggestName, TSymbol::TYPE_VOID, typeName });
		m_newVariates.append(variate);
	}

	VariateManagerWithHorizonHeader::GetInstance()->InsertVariate(std::shared_ptr<TVariate>(variate->Clone()), m_treeWidget, m_treeWidget->invisibleRootItem());

	auto item = m_treeWidget->topLevelItem(m_treeWidget->topLevelItemCount() - 1);
	m_treeWidget->setItemWidget(item, 1, variateComboBox);

	connect(variateComboBox, &QComboBox::currentTextChanged, [item, this](const QString& text){
		auto variate = TVariateManager::GetInstance()->GetVariateSrollUp(Context::projectContext.ProgramOpened(), text);
		if (variate == nullptr)
		{
			return;
		}

		VariateManagerWithHorizonHeader::GetInstance()->UpdateWidget(std::shared_ptr<TVariate>(variate->Clone()), m_treeWidget, item);
	});
}

void MacroWidgetParent::AddParameter(const QString& typeName, int index)
{
	if (m_macroParameterList.size() > index)
	{
		AddParameter(typeName, m_macroParameterList.at(index));
	}
	else
	{
		AddParameter(typeName, "");
	}
}