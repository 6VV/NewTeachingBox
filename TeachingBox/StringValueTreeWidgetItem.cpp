#include "stdafx.h"
#include "StringValueTreeWidgetItem.h"
#include <assert.h>
#include "TString.h"
#include "RegExp.h"



VariateValueTreeWidgetBuilder<StringValueTreeWidgetItem> StringValueTreeWidgetItem::builder(TString::TypeName());

std::shared_ptr<TVariate> StringValueTreeWidgetItem::GetVariate(const TSymbol& symbol, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	return std::shared_ptr<TString>(new TString(symbol, dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(0), 1))->text()));
}

void StringValueTreeWidgetItem::InsertVariateValue(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*variate) == typeid(TString));
	auto value = dynamic_cast<TString*>(variate.get())->GetValue();
	InsertLineEdit("Value", value, RegExp::STR_REG_ANY_CHAR, treeWidget, variateItem);
}

void StringValueTreeWidgetItem::UpdateWidgetValue(const std::shared_ptr<TVariate> newVariate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*newVariate) == typeid(TString));
	auto value = dynamic_cast<TString*>(newVariate.get())->GetValue();

	dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(0), 1))->setText(value);
}
