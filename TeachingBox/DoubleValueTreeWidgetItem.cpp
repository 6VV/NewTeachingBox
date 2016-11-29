#include "stdafx.h"
#include "DoubleValueTreeWidgetItem.h"
#include <assert.h>
#include "TDouble.h"


VariateValueTreeWidgetBuilder<DoubleValueTreeWidgetItem> DoubleValueTreeWidgetItem::buidler(TDouble::TypeName());

std::shared_ptr<TVariate> DoubleValueTreeWidgetItem::GetVariate(const TSymbol& symbol, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	auto value = GetDouble(treeWidget, variateItem->child(0));
	return std::shared_ptr<TDouble>(new TDouble(symbol, value));
}

void DoubleValueTreeWidgetItem::InsertVariateValue(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*variate) == typeid(TDouble));
	auto value = dynamic_cast<TDouble*>(variate.get())->GetValue();
	InsertDouble("Value", value, treeWidget, variateItem);
}

void DoubleValueTreeWidgetItem::UpdateWidgetValue(const std::shared_ptr<TVariate> newVariate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*newVariate) == typeid(TDouble));

	auto value = dynamic_cast<TDouble*>(newVariate.get())->GetValue();

	dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(0), 1))->setText(QString::number(value));
}
