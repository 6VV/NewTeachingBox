#include "stdafx.h"
#include "TOverlapWidget.h"
#include "ComboBoxInTree.h"
#include "DataStruct.h"
#include "LineEditInTree.h"
#include "TOverlap.h"


const QString TOverlapWidget::STR_MODE_ABSOLUTE{ "Absolute" };
const QString TOverlapWidget::STR_MODE_RELATIVE{ "Relative" };


void TOverlapWidget::ReadContentTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget)
{
	ComboBoxInTree* modeBox = new ComboBoxInTree(parentItem, treeWidget);
	modeBox->addItem(STR_MODE_ABSOLUTE);
	modeBox->addItem(STR_MODE_RELATIVE);

	auto value = static_cast<TOverlap*>(m_variate)->GetValue();

	switch (value.m_TransitionMode)
	{
	case tTransitionMode::kTransitionModeAbsolute:
	{
		modeBox->setCurrentText(STR_MODE_ABSOLUTE);
	}break;
	case tTransitionMode::kTransitionModeRelative:
	{
		modeBox->setCurrentText(STR_MODE_RELATIVE);
	}break;
	default:
		break;
	}

	QTreeWidgetItem* modeItem = new QTreeWidgetItem(parentItem, QStringList{ "Mode" });
	treeWidget->setItemWidget(modeItem, 1, modeBox);
	connect(modeBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SlotOnValueChanged()));

	LineEditInTree* paraEdit = new LineEditInTree(parentItem, treeWidget, QString::number(value.m_TransitionParameter), RegExp::STR_REG_FLOAT);
	QTreeWidgetItem* parameterItem = new QTreeWidgetItem(parentItem, QStringList{ "Value" });
	treeWidget->setItemWidget(parameterItem, 1, paraEdit);
	connect(paraEdit, SIGNAL(textChanged(const QString&)), this, SLOT(SlotOnValueChanged()));
}

void TOverlapWidget::OnValueChanged()
{
	WidgetItemInTree* widget = dynamic_cast<WidgetItemInTree*>(sender());
	QTreeWidgetItem* variateItem = widget->GetParentItem();
	QTreeWidget* treeWidget = widget->GetTreeWidget();

	QString mode = static_cast<QComboBox*>(treeWidget->itemWidget(variateItem->child(0), 1))->currentText();

	//tOverlapConstraint value;
	if (mode == STR_MODE_ABSOLUTE)
	{
		m_value.m_TransitionMode = tTransitionMode::kTransitionModeAbsolute;
	}
	else
	{
		m_value.m_TransitionMode = tTransitionMode::kTransitionModeRelative;
	}

	m_value.m_TransitionParameter = static_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(1), 1))->text().toDouble();

	//static_cast<TOverlap*>(m_variate)->SetValue(value);
}

TOverlapWidget::TOverlapWidget(TOverlap* overlap)
	:TVariateWidget(overlap)
{

}

TOverlapWidget::~TOverlapWidget()
{

}

tOverlapConstraint TOverlapWidget::Value() const
{
	return m_value;
}

void TOverlapWidget::UpdateVariate()
{
	static_cast<TOverlap*>(m_variate)->SetValue(m_value);
}
