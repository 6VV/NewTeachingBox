#include "stdafx.h"
#include "BoolValueTreeWidgetItem.h"
#include "TBool.h"
#include <assert.h>



const QString BoolValueTreeWidgetItem::TRUE_VALUE("True");

const QString BoolValueTreeWidgetItem::FALSE_VALUE("False");

VariateValueTreeWidgetBuilder<BoolValueTreeWidgetItem> BoolValueTreeWidgetItem::builder(TBool::TypeName());

std::shared_ptr<TVariate> BoolValueTreeWidgetItem::GetVariate(const TSymbol& symbol, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem,int index/*=0*/)
{
	auto comboBox = dynamic_cast<QComboBox*>(treeWidget->itemWidget(variateItem->child(index), 1));

	bool value=false;
	if (comboBox->currentText()==TRUE_VALUE)
	{
		value = true;
	}

	return std::shared_ptr<TVariate>(new TBool(symbol, value));
}

void BoolValueTreeWidgetItem::InsertVariateValue(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*variate) == typeid(TBool));

	auto value = dynamic_cast<TBool*>(variate.get())->GetValue();
	QString valueName = FALSE_VALUE;
	if (value)
	{
		valueName = TRUE_VALUE;
	}

	InsertComboBox("Value", { TRUE_VALUE, FALSE_VALUE }, valueName, treeWidget, variateItem);
}

void BoolValueTreeWidgetItem::UpdateWidgetValue(const std::shared_ptr<TVariate> newVariate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*newVariate) == typeid(TBool));

	auto value = dynamic_cast<TBool*>(newVariate.get())->GetValue();

	auto valueName = FALSE_VALUE;
	if (value)
	{
		valueName = TRUE_VALUE;
	}

	dynamic_cast<QComboBox*>(treeWidget->itemWidget(variateItem->child(0), 1))->setCurrentText(valueName);
}
