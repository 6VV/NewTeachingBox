#include "stdafx.h"
#include "DialogNewVariate.h"
#include "TeachingBoxContext.h"
#include "QRect"
#include "QBoxLayout"
#include "Button.h"
#include "TVariateType.h"
#include "QTreeWidget"
#include "LineEditWithRegExpAndKeyboard.h"
#include "RegExp.h"
#include "WarningManager.h"
#include "VariateTableManager.h"
#include "IEditVariate.h"
#include "VariateDatabase.h"
#include "TVariateManager.h"
#include "VariateManagerWithVerticalHeader.h"
#include "TInteger.h"
#include <memory>
#include "TVariateFactory.h"
#include "TString.h"
#include "TBool.h"
#include "TDouble.h"
#include "TPosition.h"
#include "TDynamic.h"
#include "TOverlap.h"
#include "TRefSys.h"
#include "TToolSys.h"

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
		//if (!m_variateTableManager->IsValidVariate())
		//{
		//	WarningManager::Warning(this, tr("Wrong Variate"));
		//	return;
		//}

		//auto variate = m_variateTableManager->GetVariate();
		auto variate = VariateManagerWithVerticalHeader::GetInstance()->GetVariate(m_variateTree, m_variateTree->invisibleRootItem());
		if (variate==nullptr)
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
		//UpdateVariateWidget(item->text(0));
	}

	//void DialogNewVariate::UpdateVariateWidget(const QString& currentType)
	//{
	//	m_variateTableManager->ChangeToType(currentType);
	//}

	void DialogNewVariate::UpdateText()
	{
		m_treeWidget->setHeaderLabel(tr("Type"));
		//m_variateTableManager->UpdateText();

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
		/*添加基本类型*/
		QTreeWidgetItem* itemBase = new QTreeWidgetItem(QStringList{ TVariateType::STR_CATEGORY_BASE });
		QStringList strListBase;

		itemBase->addChild(new QTreeWidgetItem(QStringList{ TInteger::TypeName() }));
		itemBase->addChild(new QTreeWidgetItem(QStringList{ TDouble::TypeName() }));
		itemBase->addChild(new QTreeWidgetItem(QStringList{ TBool::TypeName() }));
		itemBase->addChild(new QTreeWidgetItem(QStringList{ TString::TypeName() }));

		/*添加位置类型*/
		QTreeWidgetItem* itemPosition = new QTreeWidgetItem(QStringList{ TPosition::TypeName() });
		itemPosition->addChild(new QTreeWidgetItem(QStringList{ TPosition::TypeName() }));

		/*添加动态类型*/
		QTreeWidgetItem* itemDynamic = new QTreeWidgetItem(QStringList{ TDynamic::TypeName() });
		itemDynamic->addChild(new QTreeWidgetItem(QStringList{ TDynamic::TypeName() }));

		/*添加过渡类型*/
		QTreeWidgetItem* itemOverlap = new QTreeWidgetItem(QStringList{ TOverlap::TypeName() });
		itemOverlap->addChild(new QTreeWidgetItem(QStringList{ TOverlap::TypeName() }));

		/*添加坐标系类型*/
		QTreeWidgetItem* itemCoordinateSys = new QTreeWidgetItem(QStringList{ TVariateType::STR_TYPE_REF_SYS });
		itemCoordinateSys->addChild(new QTreeWidgetItem(QStringList{ TRefSys::TypeName() }));
		itemCoordinateSys->addChild(new QTreeWidgetItem(QStringList{ TToolSys::TypeName() }));

		m_treeWidget = new QTreeWidget(this);

		m_treeWidget->addTopLevelItem(itemBase);
		m_treeWidget->addTopLevelItem(itemPosition);
		m_treeWidget->addTopLevelItem(itemDynamic);
		m_treeWidget->addTopLevelItem(itemOverlap);
		m_treeWidget->addTopLevelItem(itemCoordinateSys);

		return m_treeWidget;
	}

	QWidget* DialogNewVariate::GetVariateSettingWidget()
	{
		m_variateTree = new QTreeWidget(this);
		m_variateTree->setHeaderLabels(QStringList{ "Name", "Value" });
		m_variateTree->header()->setSectionResizeMode(QHeaderView::Stretch);	//平均分布各列
		VariateManagerWithVerticalHeader::GetInstance()->InsertVariate(std::make_shared<TInteger>(TSymbol{ m_scope }, 0), m_variateTree, m_variateTree->invisibleRootItem());
		return m_variateTree; 
		//return m_variateTableManager->GetTableWidget(m_scope);
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

		//layout->addWidget(GetTitleWidget());
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