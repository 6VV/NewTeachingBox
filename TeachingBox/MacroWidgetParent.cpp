#include "stdafx.h"
#include "MacroWidgetParent.h"
#include "Button.h"
#include "TVariate.h"
#include "WarningManager.h"
#include "CodeEditor.h"


const QString MacroWidgetParent::IMAGE_LOGO_SYSTEM{ ":/new/image/Resources/Image/S.PNG" };

const QString MacroWidgetParent::IMAGE_LOGO_COORPERATER{ ":/new/image/Resources/Image/C.PNG" };

const QString MacroWidgetParent::IMAGE_LOGO_GLOBAL{":/new/image/Resources/Image/G.PNG"};

const QString MacroWidgetParent::IMAGE_LOGO_PROJECT{ ":/new/image/Resources/Image/P.PNG" };

const QString MacroWidgetParent::IMAGE_LOGO_LOCAL{ ":/new/image/Resources/Image/L.PNG" };

const QMap<MacroWidgetParent::SymbolType, QString> MacroWidgetParent::TYPE_HEADER_MAP{
	{ SymbolType::TYPE_POSITION, "p" },
	{ SymbolType::TYPE_DYNAMIC, "dyn" },
	{ SymbolType::TYPE_OVERLAP, "ovl" },
};

MacroWidgetParent::MacroWidgetParent(const QString& macroText, QWidget* parent /*= nullptr*/)
	:DialogParent(parent)
	, m_treeWidget(new QTreeWidget(this))
	, m_btnConfirm(new Button(this))
	, m_btnCancle(new Button(this))
	, m_variatesMap(std::move(TVariateManager::GetInstance()->GetVariatesMapFromScope(Context::projectContext.ProgramOpened())))
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
	connect(m_btnConfirm, SIGNAL(clicked()), this, SLOT(SlotOnButtonConfirmClicked()));
	connect(m_btnCancle, SIGNAL(clicked()), this, SLOT(SlotOnButtonCancleClicked()));
}


QMap<QString, QStringList> MacroWidgetParent::GetVariateMap(SymbolType type) const
{
	QMap<QString, QStringList> result;

	for (auto iter = m_variatesMap.begin(); iter != m_variatesMap.end(); ++iter)
	{
		QStringList variateNames;
		for (auto variate:iter.value())
		{
			if (variate->GetType() == type)
			{
				variateNames.append(variate->GetName());
			}
		}

		result[iter.key()] = variateNames;
	}

	return result;
}

ComboBoxWithParentItem* MacroWidgetParent::GetComboBox(SymbolType type) const
{
	auto variateComboBox = new ComboBoxWithParentItem(m_treeWidget);
	auto variates = GetVariateMap(type);

	for (auto iter = variates.begin(); iter != variates.end(); ++iter)
	{
		QIcon icon;
		if (iter.key() == ProjectContext::ScopeSystem())
		{
			icon.addPixmap(QPixmap(IMAGE_LOGO_SYSTEM));
		}
		else if (iter.key() == ProjectContext::ScopeCooperate())
		{
			icon.addPixmap(QPixmap(IMAGE_LOGO_COORPERATER));
		}
		else if (iter.key() == ProjectContext::ScopeGlobal())
		{
			icon.addPixmap(QPixmap(IMAGE_LOGO_GLOBAL));
		}
		else
		{
			if (iter.key().contains("."))
			{
				icon.addPixmap(QPixmap(IMAGE_LOGO_LOCAL));
			}
			else
			{
				icon.addPixmap(QPixmap(IMAGE_LOGO_PROJECT));
			}
		}

		for (auto var : iter.value())
		{
			variateComboBox->addItem(icon, var);
		}
	}

	return variateComboBox;
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

					TVariateManager::GetInstance()->AddVariate(*variate);

					/*将节点挂在新变量上，避免因原变量销毁导致指向无效地址*/
					comboBox->ParentItem()->Variate(TVariateManager::GetInstance()->GetVariateSrollUp(
						Context::projectContext.ProgramOpened(), variate->GetName()));

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

	OnConfirm();

	delete this;
}

void MacroWidgetParent::SlotOnButtonCancleClicked()
{
	for (auto comboBox : m_parameterComboBoxes)
	{
		comboBox->ParentItem()->IsSave(false);
	}
	delete this;
}

QString MacroWidgetParent::GetSuggestName(SymbolType type) const
{
	std::vector<int> suggestNamesExisted;

	auto header = TYPE_HEADER_MAP[type];

	QRegExp regExp("^" + header+"([0 - 9] + )$");
	for (auto iter = m_variatesMap.begin(); iter != m_variatesMap.end(); ++iter)
	{
		for (auto variate : iter.value())
		{
			if (regExp.exactMatch(variate->GetName()))
			{
				suggestNamesExisted.push_back(regExp.capturedTexts().at(1).toInt());
			}
		}
	}

	std::sort(suggestNamesExisted.begin(), suggestNamesExisted.end());

	int size = suggestNamesExisted.size();
	for (int i = 0; i < size; ++i)
	{
		if (suggestNamesExisted.at(i) != i)
		{
			return header + QString::number(i);
		}
	}

	return header + QString::number(suggestNamesExisted.size());
}

void MacroWidgetParent::SlotOnParameterChanged()
{
	auto comboBox = static_cast<ComboBoxWithParentItem*>(sender());

	auto parameter = comboBox->currentText();

	auto variate = TVariateManager::GetInstance()->GetVariateSrollUp(Context::projectContext.ProgramOpened(), parameter);

	if (variate==nullptr)
	{
		return;
	}

	auto parentItem = comboBox->ParentItem();
	variate->ReadContentIntoItem(parentItem, m_treeWidget);
}

void MacroWidgetParent::OnConfirm()
{
	QString text = MacroName()+" ";

	for (int i = 0; i < m_parameterComboBoxes.size(); ++i)
	{
		text += m_parameterComboBoxes.at(i)->currentText() + ",";
	}

	CodeEditor::GetInstance()->UpdateCurrentLine(text.left(text.size() - 1));
}

//void MacroWidgetParent::AddParameter(SymbolType type, const QString& name)
//{
//	auto variateComboBox = GetComboBox(type);
//
//	variateComboBox->setCurrentText(name);
//
//	auto variate = TVariateManager::GetInstance()->GetVariateSrollUp(Context::projectContext.ProgramOpened(), variateComboBox->currentText());
//
//	assert(variate != nullptr);
//
//	variate->ReadTreeWidgetItem(m_treeWidget->invisibleRootItem(), m_treeWidget);
//
//	auto item = m_treeWidget->topLevelItem(m_treeWidget->topLevelItemCount() - 1);
//
//	m_treeWidget->setItemWidget(item, 1, variateComboBox);
//}

