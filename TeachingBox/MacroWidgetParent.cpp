#include "stdafx.h"
#include "MacroWidgetParent.h"
#include "QBoxLayout"
#include "Button.h"
#include "QTreeWidget"
#include "QStringList"
#include "TVariateManager.h"
#include "Context.h"
#include "TPosition.h"
#include "QIcon"
#include "QPixmap"
#include <assert.h>



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

QComboBox* MacroWidgetParent::GetComboBox(SymbolType type) const
{
	auto variateComboBox = new QComboBox(m_treeWidget);
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

void MacroWidgetParent::AddPosition(const QString& name)
{
	auto variateComboBox = GetComboBox(SymbolType::TYPE_POSITION);

	/*if (variateComboBox->findText(name)>=0)
	{
		variateComboBox->setCurrentText(name);
	}
	else
	{
		auto suggestName = GetSuggestName(SymbolType::TYPE_POSITION);
		variateComboBox->addItem(QPixmap(IMAGE_LOGO_LOCAL), suggestName);
		variateComboBox->setCurrentText(suggestName);
	}*/

	variateComboBox->setCurrentText(name);

	auto variate = TVariateManager::GetInstance()->GetVariateSrollUp(Context::projectContext.ProgramOpened(), variateComboBox->currentText());

	assert(variate != nullptr);

	/*if (variate == nullptr)
	{
	TPosition position(Context::projectContext.ProgramOpened(), "");
	position.ReadTreeWidgetItem(m_treeWidget->invisibleRootItem(), m_treeWidget);
	}
	else
	{
	variate->ReadTreeWidgetItem(m_treeWidget->invisibleRootItem(), m_treeWidget);
	}*/
	variate->ReadTreeWidgetItem(m_treeWidget->invisibleRootItem(), m_treeWidget);

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

void MacroWidgetParent::AddParameter(SymbolType type, const QString& name)
{
	auto variateComboBox = GetComboBox(type);

	variateComboBox->setCurrentText(name);

	auto variate = TVariateManager::GetInstance()->GetVariateSrollUp(Context::projectContext.ProgramOpened(), variateComboBox->currentText());

	assert(variate != nullptr);

	variate->ReadTreeWidgetItem(m_treeWidget->invisibleRootItem(), m_treeWidget);

	auto item = m_treeWidget->topLevelItem(m_treeWidget->topLevelItemCount() - 1);

	m_treeWidget->setItemWidget(item, 1, variateComboBox);
}

