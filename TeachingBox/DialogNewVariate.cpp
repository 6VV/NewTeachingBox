#include "stdafx.h"
#include "DialogNewVariate.h"
#include "TeachingBoxContext.h"
#include "VariateManagerWithVerticalHeader.h"
#include <memory>
#include "TVariateInfo.h"
#include "TVariateFactory.h"
#include "TInteger.h"
#include "TVariateManager.h"
#include "IEditVariate.h"
#include "RegExp.h"
#include "WarningManager.h"
#include "Button.h"

namespace VariateWidget{

	DialogNewVariate::DialogNewVariate(const QString& scope, IEditVariate* iEditVariate, QWidget* parent)
		:DialogParent(parent)
		, m_scope(scope)
		, m_iEditVariate(iEditVariate)
	{
		Init();
	}

	DialogNewVariate::~DialogNewVariate()
	{

	}

	void DialogNewVariate::SlotOnConfrimButtonClicked()
	{
		auto variate = VariateManagerWithVerticalHeader::GetInstance()->GetVariate(m_variateTree, m_variateTree->invisibleRootItem());
		if (variate == nullptr)
		{
			return;
		}
		if (!CheckNameValid(variate->GetName()))
		{
			return;
		}

		m_iEditVariate->OnNewVariate(*variate);
		TVariateManager::GetInstance()->AddVariate(variate);

		Destroy();
	}

	void DialogNewVariate::SlotOnCancleButtonClicked()
	{
		Destroy();
	}

	void DialogNewVariate::SlotOnTypeChanged(QTreeWidgetItem* item)
	{
		/*若当前节点无效或为顶部节点*/
		if (item == nullptr || item->parent() == nullptr)
		{
			return;
		}

		m_variateTree->clear();
		VariateManagerWithVerticalHeader::GetInstance()->InsertVariate(
			TVariateFactory::CreateVariate(TSymbol{ m_scope, "", TSymbol::TYPE_VOID, item->text(0) }), m_variateTree, m_variateTree->invisibleRootItem());
	}

	void DialogNewVariate::UpdateText()
	{
		m_treeWidget->setHeaderLabel(tr("Type"));

		m_btnConfrim->setText(tr("Confirm"));
		m_btnCancle->setText(tr("Cancle"));
	}

	bool DialogNewVariate::CheckNameValid(const QString& name)
	{
		QRegExp regExp(RegExp::STR_REG_STRING_NAME);

		if (name.isEmpty() || !regExp.exactMatch(name))
		{
			WarningManager::Warning(this, tr("Invalid name"));
			return false;
		}

		return true;
	}

	void DialogNewVariate::Destroy()
	{
		delete this;
	}

	QLayout* DialogNewVariate::GetButtonLayout()
	{
		m_btnConfrim = new Button(this);
		m_btnCancle = new Button(this);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->addStretch(0);
		layout->addWidget(m_btnConfrim);
		layout->addStretch(0);
		layout->addWidget(m_btnCancle);
		layout->addStretch(0);

		return layout;
	}

	QLayout* DialogNewVariate::GetVariateLayout()
	{
		QHBoxLayout* layout = new QHBoxLayout(this);

		layout->addWidget(GetVariateTypeWidget());
		layout->addWidget(GetVariateSettingWidget());

		layout->setStretch(0, 1);
		layout->setStretch(1, 2);

		return layout;
	}

	QWidget* DialogNewVariate::GetVariateTypeWidget()
	{
		m_treeWidget = new QTreeWidget(this);

		auto& map = TVariateInfo::CategoryMap();

		for (auto iter:map)
		{
			QTreeWidgetItem* itemCategory = new QTreeWidgetItem(QStringList{ iter.first });
			m_treeWidget->addTopLevelItem(itemCategory);

			for (auto iterType:*iter.second)
			{
				itemCategory->addChild(new QTreeWidgetItem(QStringList{ iterType}));
			}
		}

		return m_treeWidget;
	}

	QWidget* DialogNewVariate::GetVariateSettingWidget()
	{
		m_variateTree = new QTreeWidget(this);
		m_variateTree->setHeaderLabels(QStringList{ "Name", "Value" });
		m_variateTree->header()->setSectionResizeMode(QHeaderView::Stretch);	//平均分布各列
		VariateManagerWithVerticalHeader::GetInstance()->InsertVariate(std::make_shared<TInteger>(TSymbol{ m_scope }, 0), m_variateTree, m_variateTree->invisibleRootItem());
		return m_variateTree;
	}

	void DialogNewVariate::Init()
	{
		setWindowTitle(tr("New Variate"));

		InitLayout();
		InitSignalSlot();

		UpdateText();
	}

	void DialogNewVariate::InitLayout()
	{
		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->setMargin(0);

		layout->addLayout(GetVariateLayout());
		layout->addLayout(GetButtonLayout());

		layout->setStretch(0, 1);
	}

	QWidget* DialogNewVariate::GetTitleWidget()
	{
		QLabel* titleWidget = new QLabel(tr("New Variate"), this);
		titleWidget->setStyleSheet("background:white;");
		QFont font;
		font.setPointSize(16);
		titleWidget->setFont(font);
		titleWidget->setMargin(0);

		return titleWidget;
	}

	void DialogNewVariate::InitSignalSlot()
	{
		connect(m_btnConfrim, SIGNAL(clicked()), this, SLOT(SlotOnConfrimButtonClicked()));
		connect(m_btnCancle, SIGNAL(clicked()), this, SLOT(SlotOnCancleButtonClicked()));

		connect(m_treeWidget, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(SlotOnTypeChanged(QTreeWidgetItem*)));
	}


}