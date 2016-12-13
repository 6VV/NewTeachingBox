#include "stdafx.h"
#include "OverlapValueTreeWidgetItem.h"
#include "TOverlap.h"
#include <assert.h>


const QString OverlapValueTreeWidgetItem::STR_MODE_ABSOLUTE{ "Absolute" };
const QString OverlapValueTreeWidgetItem::STR_MODE_RELATIVE{ "Relative" };

VariateValueTreeWidgetBuilder<OverlapValueTreeWidgetItem> OverlapValueTreeWidgetItem::builder(TOverlap::TypeName());

std::shared_ptr<TVariate> OverlapValueTreeWidgetItem::GetVariate(const TSymbol& symbol, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem,int index)
{
	auto modeName = dynamic_cast<QComboBox*>(treeWidget->itemWidget(variateItem->child(0 + index), 1))->currentText();

	tTransitionMode mode=tTransitionMode::kTransitionModeAbsolute;
	if (modeName == STR_MODE_RELATIVE)
	{
		mode = tTransitionMode::kTransitionModeRelative;
	}

	auto value = dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(1 + index), 1))->text().toDouble();

	return std::shared_ptr<TOverlap>(new TOverlap(symbol, { mode, value }));
}

void OverlapValueTreeWidgetItem::InsertVariateValue(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*variate) == typeid(TOverlap));
	auto value = dynamic_cast<TOverlap*>(variate.get())->GetValue();

	InsertModeValue(value.m_TransitionMode,treeWidget, variateItem);
	InsertDouble("Value", value.m_TransitionParameter, treeWidget, variateItem);

}

void OverlapValueTreeWidgetItem::InsertModeValue(int mode,QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	QString modeName = STR_MODE_ABSOLUTE;
	if (mode == tTransitionMode::kTransitionModeRelative)
	{
		modeName = STR_MODE_RELATIVE;
	}

	InsertComboBox("Mode", { STR_MODE_RELATIVE, STR_MODE_ABSOLUTE }, modeName, treeWidget, variateItem);

	//QComboBox* comboBox = new QComboBox(treeWidget);
	//comboBox->addItems({ STR_MODE_RELATIVE, STR_MODE_ABSOLUTE });

	//QTreeWidgetItem* modeItem = new QTreeWidgetItem(variateItem);
	//modeItem->setText(0, "Mode");
	//treeWidget->setItemWidget(modeItem, 1, comboBox);
	//comboBox->setCurrentText(modeName);

	//connect(comboBox, &QComboBox::currentTextChanged, [this, variateItem]{emit(SignalValueChanged(variateItem)); });
}

void OverlapValueTreeWidgetItem::UpdateWidgetValue(const std::shared_ptr<TVariate> newVariate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*newVariate) == typeid(TOverlap));
	auto value = dynamic_cast<TOverlap*>(newVariate.get())->GetValue();

	auto modeName = STR_MODE_ABSOLUTE;
	if (value.m_TransitionMode == tTransitionMode::kTransitionModeRelative)
	{
		modeName = STR_MODE_RELATIVE;
	}

	dynamic_cast<QComboBox*>(treeWidget->itemWidget(variateItem->child(0), 1))->setCurrentText(modeName);
	dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(1), 1))->setText(QString::number(value.m_TransitionParameter));
}
