#include "stdafx.h"
#include "IntegerValueTreeWidgetItem.h"
#include <assert.h>
#include "TInteger.h"



VariateValueTreeWidgetBuilder<IntegerValueTreeWidgetItem> IntegerValueTreeWidgetItem::builder(TInteger::TypeName());

void IntegerValueTreeWidgetItem::InsertVariateValue(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*variate) == typeid(TInteger));
	int value = dynamic_cast<TInteger*>(variate.get())->GetValue();
	InsertInt("Value", value, treeWidget, variateItem);
}


void IntegerValueTreeWidgetItem::UpdateWidgetValue(const std::shared_ptr<TVariate> newVariate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*newVariate) == typeid(TInteger));

	auto value = dynamic_cast<TInteger*>(newVariate.get())->GetValue();

	dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(0), 1))->setText(QString::number(value));
}

std::shared_ptr<TVariate> IntegerValueTreeWidgetItem::GetVariate(const TSymbol& symbol, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem,int index)
{
	int value = GetInt(treeWidget, variateItem->child(index));
	return std::shared_ptr<TInteger>(new TInteger(symbol,value));
}

